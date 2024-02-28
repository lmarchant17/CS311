#include <stdio.h>

struct int_list_item {
    int number;              // 4 bytes
    int_list_item* next;     // 8 bytes
};

struct int_list {
    int_list_item* first_node = 0;
};

void add_number(int_list& list, int number) {
    if (!list.first_node) {
        list.first_node = new int_list_item;
        list.first_node->number = number;
        list.first_node->next = 0;
        return;
    }

    int_list_item* place = list.first_node;
    for (; place->next; place = place->next);
    place->next = new int_list_item;
    place->next->number = number;
    place->next->next = 0;
}

void push(int_list& list, int number) {
    int_list_item* new_item = new int_list_item;
    new_item->number = number;
    new_item->next = list.first_node;
    list.first_node = new_item;
}

int pop(int_list& list) {
    if (!list.first_node) {
        // List is empty error
        return -1;
    }

    int number = list.first_node->number;
    int_list_item* temp = list.first_node;
    list.first_node = list.first_node->next;
    delete temp;
    return number;
}

bool remove(int_list& list, int index) {
    if (!list.first_node) {
        // List is empty error
        return false;
    }

    if (index == 0) {
        int_list_item* temp = list.first_node;
        list.first_node = list.first_node->next;
        delete temp;
        return true;
    }

    int_list_item* place = list.first_node;
    for (int i = 0; i < index - 1; i++) {
        if (!place->next) {
            // Index out of bounds error
            return false;
        }
        place = place->next;
    }

    int_list_item* temp = place->next;
    place->next = place->next->next;
    delete temp;
    return true;
}

bool contains(const int_list& list, int number) {
    int_list_item* place = list.first_node;
    while (place) {
        if (place->number == number) {
            return true;
        }
        place = place->next;
    }
    return false;
}

int main() {
    int_list test_list;
    add_number(test_list, 240);
    add_number(test_list, 310);
    add_number(test_list, 435);

    // Let's print them out!
    for (int_list_item* place = test_list.first_node; place; place = place->next) {
        printf("%d (stored at address %p)\n", place->number, &place->number);
    }

    push(test_list, 100);
    push(test_list, 200);

    printf("\nAfter push:\n");
    for (int_list_item* place = test_list.first_node; place; place = place->next) {
        printf("%d (stored at address %p)\n", place->number, &place->number);
    }

    printf("\nPop: %d\n", pop(test_list));

    printf("\nAfter pop:\n");
    for (int_list_item* place = test_list.first_node; place; place = place->next) {
        printf("%d (stored at address %p)\n", place->number, &place->number);
    }

    printf("\nRemove at index 1: %s\n", remove(test_list, 1) ? "Success" : "Failed");

    printf("\nAfter remove:\n");
    for (int_list_item* place = test_list.first_node; place; place = place->next) {
        printf("%d (stored at address %p)\n", place->number, &place->number);
    }

    printf("\nContains 240: %s\n", contains(test_list, 240) ? "Yes" : "No");
    printf("Contains 999: %s\n", contains(test_list, 999) ? "Yes" : "No");

    return 0;
}