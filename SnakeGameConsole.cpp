#include<cstdlib>
#include<conio.h>
#include<iostream>
#include<deque>
#include<thread>

using namespace std;

// Size of area
const int WIDTH = 20;
const int HEIGHT = 20;

struct Position {
    int x, y;
    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
};

enum Direction { UP, DOWN, LEFT, RIGHT };


//function for draw the area
void draw(const deque<Position>& snake, const Position& food) {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            Position current = { x, y };
            if (find(snake.begin(), snake.end(), current) != snake.end()) {
                cout << "O"; // snake body
            }
            else if (food == current) {
                cout << "*"; // food
            }
            else {
                cout << " "; // empty space
            }
        }
        cout << "\n";
    }
}

// generation food on the area
Position generate_food(const deque<Position>& snake) {
    Position food;
    do {
        food = { rand() % WIDTH, rand() % HEIGHT };
    } while (find(snake.begin(), snake.end(), food) != snake.end());
    return food;
}

int main() {
    deque<Position> snake = { {5, 5}, {4, 5}, {3, 5} }; // start snake
    Position food = generate_food(snake);
    Direction dir = RIGHT;
    bool game_over = false;

    while (!game_over) {
        system("cls"); // clear of the console
        draw(snake, food);

        // processing of enter
        if (_kbhit()) {
            switch (_getch()) {
            case 'w': dir = UP; break;
            case 's': dir = DOWN; break;
            case 'a': dir = LEFT; break;
            case 'd': dir = RIGHT; break;
            }
        }
        // new head
        Position new_head = snake.front();
        switch (dir) {
        case UP:    new_head.y--; break;
        case DOWN:  new_head.y++; break;
        case LEFT:  new_head.x--; break;
        case RIGHT: new_head.x++; break;
        }

        // check on the collision
        if (new_head.x < 0 || new_head.x >= WIDTH ||
            new_head.y < 0 || new_head.y >= HEIGHT ||
            find(snake.begin(), snake.end(), new_head) != snake.end()) {
            game_over = true;
            break;
        }

        snake.push_front(new_head);

        // check of the food
        if (new_head == food) {
            food = generate_food(snake); // new food
        }
        else {
            snake.pop_back(); // delere of the tail
        }

        // delay
        this_thread::sleep_for(chrono::milliseconds(200));
    }

    cout << "Game Over!\n";
    return 0;
}
