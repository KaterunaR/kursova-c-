#include "Store.h"

using namespace std;

int main()
{
    try
    {
        Store store;
        int choice;
        do {
            store.displayMenu();
            cin >> choice;
            store.processChoice(choice);
        } while (choice != 7);
    }
    catch (const exception& ex)
    {
        cout << "Exception occurred: " << ex.what() << "\n";
    }

    return 0;
}