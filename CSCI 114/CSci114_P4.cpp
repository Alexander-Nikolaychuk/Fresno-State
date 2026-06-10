// CSci114_P4.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <cstdlib>

using namespace std;

enum Direction { NORTH = 0, SOUTH = 1, NONE = -1 };

string returnDir(Direction d) {
    return d == NORTH ? "north" : "south";
}

struct Car {
    int globalId;
    int dirId;
    Direction dir;
};

int N;
vector<Car> cars;

mutex mtx;
condition_variable cv;

int nextArrival = 1;

queue<int> waitQueue[2];
int waitingCount[2] = {0, 0};

Direction tunnelDir = NONE;
int carsInTunnel = 0;
int consecutive = 0;
Direction lastDir = NONE;
Direction turn = NONE;


bool canEnter(const Car& car) {
    int d = car.dir;
    int od = 1 - d;

    if (waitQueue[d].empty() || waitQueue[d].front() != car.globalId)
        return false;

    if (tunnelDir != NONE && tunnelDir != car.dir)
        return false;

    if (turn != NONE && car.dir != turn)
        return false;

    if (turn == NONE &&
        lastDir == car.dir &&
        consecutive >= N &&
        waitingCount[od] > 0)
        return false;

    return true;
}





void carThread(Car car) {
    unique_lock<mutex> lock(mtx);

    cv.wait(lock, [&] {
        return car.globalId == nextArrival;
    });

    cout << "#" << car.dirId << " " << returnDir(car.dir)
         << " direction car arriving" << endl;

    waitQueue[car.dir].push(car.globalId);
    waitingCount[car.dir]++;

    cout << "#" << car.dirId << " " << returnDir(car.dir)
         << " direction car waiting" << endl;

    if (waitingCount[car.dir] == N) {
        cout << N << " " << returnDir(car.dir)
             << " direction cars have been waiting" << endl;
    }

    nextArrival++;
    cv.notify_all();

    cv.wait(lock, [&] {
        return canEnter(car);
    });

    waitQueue[car.dir].pop();
    waitingCount[car.dir]--;

    if (tunnelDir == NONE)
        tunnelDir = car.dir;

    carsInTunnel++;

    if (lastDir == car.dir)
        consecutive++;
    else {
        lastDir = car.dir;
        consecutive = 1;
    }

    cout << "#" << car.dirId << " " << returnDir(car.dir)
         << " direction car entering the tunnel" << endl;

    lock.unlock();

    this_thread::sleep_for(chrono::milliseconds(50));

    lock.lock();

    carsInTunnel--;

    cout << "#" << car.dirId << " " << returnDir(car.dir)
         << " direction car leaving the tunnel" << endl;

    if (consecutive == N) {
        cout << "Nth car has left the tunnel" << endl;
    }

    if (carsInTunnel == 0) {
        tunnelDir = NONE;

        int od = 1 - car.dir;

        if (waitingCount[NORTH] >= N)
            turn = NORTH;
        else if (waitingCount[SOUTH] >= N)
              turn = SOUTH;
    }

    cv.notify_all();
}





int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: ./P4.exe (Number of cars per direction)" << endl;
        return 1;
    }

    N = atoi(argv[1]);

    if (N < 5 || N > 15) {
        cerr << "N must be between 5 and 15" << endl;
        return 1;
    }

    ifstream filein("cars.txt");

    if (!filein) {
        cerr << "Could not open cars.txt" << endl;
        return 1;
    }

    string dir;
    int globalId = 1;
    int northId = 1;
    int southId = 1;

    // Fill up car vector
    while (filein >> dir) {
        Car car;
        car.globalId = globalId++;

        if (dir == "N") {
            car.dir = NORTH;
            car.dirId = northId++;
        } else {
            car.dir = SOUTH;
            car.dirId = southId++;
        } 
        cars.push_back(car);
    }

    vector<thread> threads;

    for (const Car& car : cars) {
        threads.emplace_back(carThread, car);
    }

    for (thread& t : threads) {
        t.join();
    }

    cout << "All cars have passed through the tunnel." << endl;

    return 0;
}
