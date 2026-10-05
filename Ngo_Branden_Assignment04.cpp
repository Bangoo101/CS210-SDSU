#include <iostream>
#include <vector>
#include <string>
#include <random> 
using namespace std;

class MonopolyBoard{
    public:
        class BoardSpace{
            private:
            string name;
            string type;
            int cost;
            bool purchased;
            double rent;
            string owner;

            public:
            BoardSpace(string n,string t, int c = 0, bool p = false, double r = 0.0)
                : name(n), type(t), cost(c), purchased(p), rent(r), owner("") {}

            bool isProperty() const {
                return type == "PROPERTY";
            }

            bool isPurchased() const {
                return purchased;
            }

            int getCost() const {
                return cost;
            }

            double getRent() const {
                return rent;
            }

            string getName() const {
                return name;
            }

            string getOwner() const {
                return owner;
            }

            void purchase(string playerName) {
                purchased = true;
                owner = playerName;
            }

            void displaySpace() const{
                cout << "(NAME: " << name << " ) " 
                     << "(TYPE: " << type << " ) " 
                     << "(COST: " << cost << " ) " 
                     << "(PURC: " << purchased << " ) "
                     << "(RENT: " << rent << " ) ";

                if (purchased) {
                    cout << "(OWNER: " << owner << " ) ";
                }

                cout << endl;
            }
        };

        struct Node {
            BoardSpace space;
            Node* next;
            Node* prev;
        };
    private:
        Node* first = nullptr;
        Node* last = nullptr;

        struct Player {
            string name;
            double money;
            Node* position;
        };

        Player player1{"Player 1", 1500, nullptr};
        Player player2{"Player 2", 1500, nullptr};

    public:
    
        void addSpace(BoardSpace space) {
            Node* newNode = new Node{space, nullptr, nullptr};

            if (first == nullptr) {
                first = newNode;
                last = newNode;

                first->next = first;
                first->prev = first;
            }
            else {
                newNode->next = first;
                newNode->prev = last;

                last->next = newNode;
                first->prev = newNode;

                last = newNode;
            }
        }

        void initializeBoard(){ //12 spaces not including railroads or utilities
            addSpace(BoardSpace("GO","SPECIAL"));
            addSpace(BoardSpace("Baltic Ave","PROPERTY", 60, false, 4));
            addSpace(BoardSpace("Chance", "SPECIAL"));
            addSpace(BoardSpace("Connecticut Ave", "PROPERTY", 120, false, 8));
            addSpace(BoardSpace("Virginia Ave", "PROPERTY", 160,false, 12));
            addSpace(BoardSpace("New York Ave", "PROPERTY", 200,false, 16));
            addSpace(BoardSpace("Free Parking", "SPECIAL"));
            addSpace(BoardSpace("Illinois Ave", "PROPERTY", 240,false, 20));
            addSpace(BoardSpace("Marvin Gardens", "PROPERTY", 280,false, 24));
            addSpace(BoardSpace("Community Chest", "SPECIAL"));
            addSpace(BoardSpace("Pennsylvania Ave", "PROPERTY", 320,false, 28));
            addSpace(BoardSpace("Boardwalk", "PROPERTY", 400, false, 50));
        }

        void printBoard() const {
            cout << "--- Monopoly Board Layout ---" << endl;

            if (first == nullptr) {
                cout << "ERROR: Board is empty." << endl;
                return;
            }

            Node* current = first;

            do {
                current->space.displaySpace();
                current = current->next;
            } while (current != first);
        }

        void initializePlayers() {
            player1.position = first;
            player2.position = first;
        }

        int rollDie() const {
            static random_device rd;
            static mt19937 gen(rd());
            uniform_int_distribution<int> dist(1, 6);
            return dist(gen);
        }

        void movePlayer(Player& player, int spacesToMove) {
            if (first == nullptr) {
                return;
            }

            cout << player.name << " rolled a " << spacesToMove << endl;

            for (int i = 0; i < spacesToMove; i++) {
                player.position = player.position->next;
            }

            cout << player.name << " landed on: ";
            player.position->space.displaySpace();

            handleLanding(player);
        }

        void handleLanding(Player& player) {
            Node* space = player.position;

            if (!space->space.isProperty()) {
                return;
            }

            if (!space->space.isPurchased()) {
                if (player.money >= space->space.getCost()) {
                    player.money -= space->space.getCost();
                    space->space.purchase(player.name);

                    cout << player.name << " bought "
                         << space->space.getName()
                         << " for $" << space->space.getCost() << "." << endl;
                    cout << player.name << " now has $"
                         << player.money << endl;
                }
                else {
                    cout << player.name << " cannot afford "
                         << space->space.getName() << "." << endl;
                }
            }
            else if (space->space.getOwner() != player.name) {
                Player* owner = nullptr;

                if (space->space.getOwner() == player1.name) {
                    owner = &player1;
                }
                else if (space->space.getOwner() == player2.name) {
                    owner = &player2;
                }

                if (owner != nullptr) {
                    double rent = space->space.getRent();

                    if (player.money >= rent) {
                        player.money -= rent;
                        owner->money += rent;

                        cout << player.name << " paid $"
                             << rent << " rent to " << owner->name
                             << " for landing on "
                             << space->space.getName() << "." << endl;
                    }
                    else {
                        cout << player.name << " cannot afford the $"
                             << rent << " rent." << endl;
                    }

                    cout << player.name << " now has $"
                         << player.money << endl;
                    cout << owner->name << " now has $"
                         << owner->money << endl;
                }
            }
            else {
                cout << player.name << " landed on their own property." << endl;
            }
        }

        void playTurn(Player& player) {
            int roll = rollDie();
            movePlayer(player, roll);
        }

        void playGame(int numberOfRounds) {
            if (first == nullptr) {
                return;
            }

            initializePlayers();

            cout << "--- Two Player Game ---" << endl;
            cout << player1.name << " starts with $" << player1.money << endl;
            cout << player2.name << " starts with $" << player2.money << endl;

            for (int round = 1; round <= numberOfRounds; round++) {
                cout << "\n--- Round " << round << " ---" << endl;

                playTurn(player1);
                playTurn(player2);

                cout << "Money: " << player1.name << " = $"
                     << player1.money << ", "
                     << player2.name << " = $"
                     << player2.money << endl;
            }
        }

        void checkWin(){
            cout << "------ RESULTS ------" << endl;
            if (player1.money == player2.money){
                cout << "Player 1 and Player 2 draw" << endl;
            } else if (player1.money < player2.money){
                cout << "Player 1 loses and Player 2 wins" << endl;
            } else if (player1.money > player2.money){
                cout << "Player 1 wins and Player 2 loses" << endl;
            } else {
                cout << "ERROR: money not equal, greater or lesser than" << endl;
            }
        }

        ~MonopolyBoard() {
            if (first == nullptr) {
                return;
            }

            last->next = nullptr;
            first->prev = nullptr;

            Node* current = first;

            while (current != nullptr) {
                Node* nextNode = current->next;
                delete current;
                current = nextNode;
            }
        }
};

int main(){
    MonopolyBoard board;
    board.initializeBoard();
    board.printBoard();
    board.playGame(10);
    board.checkWin();
    return 0;
}
//No gui cus i turned 21 and i wanna drink instead of make a gui (making dui's instead frfr) (not*)