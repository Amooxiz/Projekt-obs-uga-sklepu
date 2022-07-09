#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <limits.h>
#define N 200
/*2) Obs³uga sklepu
Program do obs³ugi sklepu umo¿liwiaj¹cy rejestracjê towarów i klientów oraz zamówieñ. Ka¿dy towar jest opisany
atrybutami: identyfikator, nazwa, kategoria, cena. Dane klienta to: imiê, nazwisko, adres, email, telefon kontaktowy. Program
powinien umo¿liwiaæ dodawanie, usuwanie, edycjê, wypisywanie, wyszukiwanie towarów oraz klientów. Kupno towarów
odbywa siê poprzez z³o¿enie zamówienia. Ka¿de zamówienie ma identyfikator, datê z³o¿enia, dane klienta, adres dostawy,
dane towaru, liczbê sztuk, cenê, oraz status (w realizacji – stan pocz¹tkowy po z³o¿eniu, wys³ane, anulowane). Program
powinien umo¿liwiaæ zmianê stanu zamówienia z „w realizacji” na „wys³ane” lub na „anulowane”. Powinna byæ dostêpna
opcja wyœwietlania zamówieñ z³o¿onych przez danego klienta oraz zamówieñ z³o¿onych na dany towar. Przy wyœwietlaniu
list z danymi nale¿y dodaæ sortowanie wg wybranych pól.*/
typedef struct list_of_product
{
    int id;
    float price;
    char name[N], category[N];
    struct list_of_product * next;
} list_of_product;

typedef struct list_of_client
{
    char name[N], last_name[N], adress[N], email[N], phone[N];
    struct list_of_client * next;
} list_of_client;

typedef struct list_of_orders
{
    int order_id, the_number_of_items, product_id;
    float price_of_product, total_price;
    char date_of_submission[N], delivery_adress[N], status[N], name_of_client[N], last_name[N], adress_of_client[N], email[N], phone[N], name_of_product[N], category[N];
    struct list_of_orders* next;
} list_of_orders;

//Funckje do operowania na liscie list_of_client
void list_add_client(list_of_client **head_of_client, char *name, char *last_name, char *adress, char *email, char *phone);
void load_client(const char *fn2, list_of_client **head1);
void list_of_clients_print (list_of_client *head_of_client);
void deallocate_clients (list_of_client **head_of_client);
void remove_client (list_of_client **head_of_client, int number);
void search_client (list_of_client* head_of_client, char *name, char *last_name);
void edit_client (list_of_client **head_of_client, int number, char *name, char *last_name, char *adress, char *email, char *phone);
void save_list_of_client_to_file (list_of_client* head_of_client, const char *fn2);

//Funkcje do operowania na liscie list_of_product
void list_add_product (list_of_product **head_of_product, int id, char *name, char *category, float price);
void load_product(const char *fn1, list_of_product **head_of_product);
void list_of_products_print (list_of_product *head_of_product);
void deallocate_product (list_of_product **head_of_product);
void remove_product (list_of_product **head_of_product, int number);
void search_product (list_of_product* head_of_product, char *name);
void edit_product (list_of_product **head_of_product, int number, int id, char *name, char *category, float price);
void save_list_of_product_to_file (list_of_product *head_of_product, const char *fn1);
void remove_order (list_of_orders **head_of_order, int number);
int check_if_id_of_product_appears(list_of_product* head_of_product, int id);

//Funkcje do operowania na liscie list_of_orders
void save_list_of_order_to_file (const char *fn3, list_of_orders* head_of_order);
void remove_order (list_of_orders **head_of_order, int number);
void insert_order (list_of_orders **head_of_orders, list_of_client* head_of_client, list_of_product* head_of_product, int number_of_client, int number_of_product, int order_id, int the_number_of_items, char *date_of_submission, char *delivery_adress);
void list_add_order (list_of_orders **head_of_orders, int order_id, int product_id, int the_number_of_items, char *name_of_client, char *last_name, char *adress_of_client, char *email, char *phone, char *name_of_product, char *category, char *delivery_adress, char *date_of_submission, char *status, float price_of_product, float total_price);
void load_order(const char *fn3, list_of_orders **head_of_orders);
void list_of_order_print (list_of_orders* head_of_order);
void search_order (list_of_orders* head_of_orders, int id);
int check_if_id_of_order_appears (list_of_orders* head_of_orders, int id);
void change_status (list_of_orders* head_of_orders, int id, char *status);
void print_orders_with_same_client (list_of_orders* head_of_order, char *name, char *surname);
void print_orders_with_same_product (list_of_orders* head_of_order, int product_id);
void deallocate_orders (list_of_orders **head_of_orders);

void Break()
{
    printf("\n=================================================================\n\n");
    return;
}
void list_add_product (list_of_product **head_of_product, int id, char *name, char *category, float price)
{
    list_of_product* new_node = (list_of_product*)malloc(sizeof(list_of_product));
    if (new_node == NULL)
    {
        exit(2);
    }
    new_node->id = id;
    strcpy(new_node->name,name);
    strcpy(new_node->category,category);
    new_node->price = price;
    if (*head_of_product == NULL)
    {
        *head_of_product = new_node;
        new_node->next = NULL;
        return;
    }
    list_of_product* tmp = *head_of_product;
    while (tmp->next != NULL)
    {
        tmp = tmp->next;
    }
    tmp->next = new_node;
    new_node->next = NULL;
    return;
}
void list_add_client(list_of_client **head_of_client, char *name, char *last_name, char *adress, char *email, char *phone)
{
    list_of_client* new_node = (list_of_client*)malloc(sizeof(list_of_client));
    if (new_node == NULL)
    {
        exit(1);
    }
    strcpy(new_node->name,name);
    strcpy(new_node->last_name,last_name);
    strcpy(new_node->adress,adress);
    strcpy(new_node->email,email);
    strcpy(new_node->phone,phone);
    if (*head_of_client == NULL)
    {
        *head_of_client = new_node;
        new_node->next = NULL;
        return;
    }
    list_of_client* tmp = *head_of_client;
    while (tmp->next != NULL)
    {
        tmp = tmp->next;
    }
    tmp->next = new_node;
    new_node->next = NULL;
    return;
}
void load_product(const char *fn1, list_of_product **head_of_product)
{
    FILE* f1 = fopen(fn1,"r");
    if (f1==NULL)
    {
        printf("Eror: cant open file");
        return;
    }

    int id;
    float price;
    char name[N], category[N];

    list_of_product** curr = head_of_product;
    while (fscanf(f1,"%d%s%s%f", &id, name, category, &price)==4)
    {
        list_add_product(curr, id, name, category, price);
    }
    fclose(f1);

    return;
}
void load_client(const char *fn2, list_of_client **head1)
{
    FILE* f2 = fopen(fn2,"r");
    if (f2==NULL)
    {
        printf("Eror: cant open file");
        return;
    }

    char name[N], last_name[N], adress[N], email[N], phone[N];
    list_of_client** curr = head1;
    while (fscanf(f2,"%s%s%s%s%s", name, last_name, adress, email, phone)==5)
    {
        list_add_client(curr, name, last_name, adress, email, phone);
    }
    fclose(f2);

    return;
}
void list_of_clients_print (list_of_client *head_of_client)
{
    printf("list elements:\n");
    if (head_of_client==NULL)
    {
        printf("list is empty\n");
        return;
    }
    int i=1;
    while (head_of_client != NULL)
    {
        printf("%d %s %s %s %s %s\n", i, head_of_client->name, head_of_client->last_name, head_of_client->adress, head_of_client->email, head_of_client->phone);
        head_of_client = head_of_client->next;
        i++;
    }
    return;
}
void list_of_products_print (list_of_product *head_of_product)
{
    printf("list elements:\n");
    if (head_of_product==NULL)
    {
        printf("list is empty\n");
        return;
    }
    int i=1;
    while (head_of_product != NULL)
    {
        printf("%d %d %s %s %.2f\n", i, head_of_product->id, head_of_product->name, head_of_product->category, head_of_product->price);
        head_of_product = head_of_product->next;
        i++;
    }
    return;
}
void deallocate_clients (list_of_client **head_of_client)
{
    list_of_client* curr = *head_of_client;
    while (curr != NULL)
    {
        list_of_client* tmp = curr;
        curr = curr->next;
        free(tmp);
    }
    *head_of_client = NULL;
    return;
}
void deallocate_product (list_of_product **head_of_product)
{
    list_of_product* curr = *head_of_product;
    while (curr != NULL)
    {
        list_of_product* tmp = curr;
        curr = curr->next;
        free(tmp);
    }
    *head_of_product = NULL;
    return;
}
void remove_client (list_of_client **head_of_client, int number)
{
    int count=1;
    if (*head_of_client == NULL)
    {
        printf("list is empty\n");
        Sleep(2000);
        system("cls");
        return;
    }

    if (number == 1)
    {
        list_of_client* to_remove = *head_of_client;
        *head_of_client = (*head_of_client)->next;
        free(to_remove);
        printf("Client removed successfully\n");
        Sleep(2000);
        system("cls");
        return;
    }

    list_of_client* curr = *head_of_client;
    while (curr->next != NULL)
    {
        if (count == (number-1))
        {
            list_of_client* to_remove = curr->next;
            curr->next = curr->next->next;
            free(to_remove);
            printf("Client removed successfully\n");
            Sleep(2000);
            system("cls");
            return;
        }
        count++;
        curr = curr->next;
    }
    printf("the number you entered exceeds the list items\n");
    Sleep(2000);
    system("cls");
    return;
}
void remove_product (list_of_product **head_of_product, int number)
{
    int count=1;
    if (*head_of_product == NULL)
    {
        printf("list is empty\n");
        return;
    }

    if (number == 1)
    {
        list_of_product* to_remove = *head_of_product;
        *head_of_product = (*head_of_product)->next;
        free(to_remove);
        printf("Product deleted succesfully\n");
        Sleep(2000);
        system("cls");
        return;
    }

    list_of_product* curr = *head_of_product;
    while (curr->next != NULL)
    {
        if (count == (number-1))
        {
            list_of_product* to_remove = curr->next;
            curr->next = curr->next->next;
            free(to_remove);
            printf("Product deleted succesfully\n");
            Sleep(2000);
            system("cls");
            return;
        }
        count++;
        curr = curr->next;
    }
    printf("The number you entered exceeds the list items\n");
    Sleep(2000);
    system("cls");
    return;
}
void search_client (list_of_client* head_of_client, char *name, char *last_name)
{
    while (head_of_client != NULL)
    {
        if (strcmp(head_of_client->name, name) == 0 && strcmp(head_of_client->last_name, last_name) == 0)
        {
            printf("%s %s %s %s %s\n", head_of_client->name, head_of_client->last_name, head_of_client->adress, head_of_client->email, head_of_client->phone);
            return;
        }
        head_of_client = head_of_client->next;
    }
    printf("The customer with the given name and surname is not on the list\n");
    Sleep(3000);
    system("cls");
    return;
}
void search_product (list_of_product* head_of_product, char *name)
{
    while (head_of_product != NULL)
    {
        if (strcmp(head_of_product->name, name) == 0)
        {
            printf("%d %s %s %.2f\n", head_of_product->id, head_of_product->name, head_of_product->category, head_of_product->price);
            return;
        }
        head_of_product = head_of_product->next;
    }
    printf("The product with the given name is not on the list\n");
    Sleep(2000);
    system("cls");
    return;
}
void edit_client (list_of_client **head_of_client, int number, char *name, char *last_name, char *adress, char *email, char *phone)
{
    int count=1;
    list_of_client* curr = *head_of_client;
    while (curr != NULL)
    {
        if (count == number)
        {
            strcpy(curr->name, name);
            strcpy(curr->last_name, last_name);
            strcpy(curr->adress, adress);
            strcpy(curr->email, email);
            strcpy(curr->phone, phone);
            return;
        }
        count++;
        curr = curr->next;
    }
    printf("the number you entered exceeds the list items\n");
    Sleep(2000);
    system("cls");
    return;
}
void edit_product (list_of_product **head_of_product, int number, int id, char *name, char *category, float price)
{
    int count=1;
    list_of_product* curr = *head_of_product;
    while (curr != 0)
    {
        if (count == number)
        {
            curr->id = id;
            strcpy(curr->name, name);
            strcpy(curr->category, category);
            curr->price = price;
            printf("Product edited succesfully\n");
            Sleep(2000);
            system("cls");
            return;
        }
        count++;
        curr = curr->next;
    }
    printf("the number you entered exceeds the list items\n");
    Sleep(2000);
    system("cls");
    return;
}
void save_list_of_client_to_file (list_of_client* head_of_client, const char *fn2)
{
    FILE* f2 = fopen(fn2,"w+");
    if (f2 == NULL)
    {
        printf("Error: cant open file\n");
        return;
    }
    if (head_of_client == NULL)
    {
        printf("Cant save empty list to file\n");
        Sleep(2000);
        system("cls");
        return;
    }
    while (head_of_client != NULL)
    {
        fprintf(f2,"%s %s %s %s %s\n", head_of_client->name, head_of_client->last_name, head_of_client->adress, head_of_client->email, head_of_client->phone);
        head_of_client = head_of_client->next;
    }
    printf("list successfully saved\n");
    Sleep(2000);
    system("cls");
    return;
}
void save_list_of_product_to_file (list_of_product *head_of_product, const char *fn1)
{
    FILE* f1 = fopen(fn1,"w+");
    if (f1 == NULL)
    {
        printf("Error: cant open file\n");
        return;
    }
    if (head_of_product == NULL)
    {
        printf("Cant save empty list to file\n");
        Sleep(2000);
        system("cls");
        return;
    }
    while (head_of_product != NULL)
    {
        fprintf(f1,"%d %s %s %.2f\n", head_of_product->id, head_of_product->name, head_of_product->category, head_of_product->price);
        head_of_product = head_of_product->next;
    }
    printf("list successfully saved\n");
    Sleep(2000);
    system("cls");
    return;
}
void save_list_of_order_to_file (const char *fn3, list_of_orders* head_of_order)
{
    FILE* f3 = fopen(fn3,"w+");
    if (f3 == NULL)
    {
        printf("Error: cant open file\n");
        return;
    }
    if (head_of_order == NULL)
    {
        printf("Cant save empty list to file\n");
        Sleep(2000);
        system("cls");
        return;
    }
    while (head_of_order != NULL)
    {
        fprintf(f3,"%d %d %d %s %s %s %s %s %s %s %s %s %s %.2f %.2f\n", head_of_order->order_id, head_of_order->product_id, head_of_order->the_number_of_items, head_of_order->name_of_client, head_of_order->last_name, head_of_order->adress_of_client, head_of_order->email, head_of_order->phone, head_of_order->name_of_product, head_of_order->category, head_of_order->delivery_adress, head_of_order->date_of_submission, head_of_order->status, head_of_order->price_of_product, head_of_order->total_price);
        head_of_order = head_of_order->next;
    }
    printf("list successfully saved\n");
    Sleep(2000);
    system("cls");
    return;
}
void remove_order (list_of_orders **head_of_order, int number)
{
    int count=1;
    if (*head_of_order == NULL)
    {
        printf("list is empty\n");
        Sleep(2000);
        system("cls");
        return;
    }

    if (number == 1)
    {
        list_of_orders* to_remove = *head_of_order;
        *head_of_order = (*head_of_order)->next;
        free(to_remove);
        printf("Order removed successfully\n");
        Sleep(2000);
        system("cls");
        return;
    }

    list_of_orders* curr = *head_of_order;
    while (curr->next != NULL)
    {
        if (count == (number-1))
        {
            list_of_orders* to_remove = curr->next;
            curr->next = curr->next->next;
            free(to_remove);
            printf("Order removed successfully\n");
            Sleep(2000);
            system("cls");
            return;
        }
        count++;
        curr = curr->next;
    }
    printf("The number you entered exceeds the list items\n");
    Sleep(2000);
    system("cls");
    return;
}
void insert_order (list_of_orders **head_of_orders, list_of_client* head_of_client, list_of_product* head_of_product, int number_of_client, int number_of_product, int order_id, int the_number_of_items, char *date_of_submission, char *delivery_adress)
{
    char status[12] = "in_progress";
    int count_product = 1;
    int count_client = 1;
    list_of_orders* new_node = (list_of_orders*)malloc(sizeof(list_of_orders));
    if (new_node == NULL)
    {
        exit(4);
    }
    while (count_client < number_of_client)
    {
        head_of_client = head_of_client->next;
        count_client++;
    }
    while (count_product < number_of_product)
    {
        head_of_product = head_of_product->next;
        count_product++;
    }
    new_node->order_id = order_id;
    strcpy(new_node->date_of_submission, date_of_submission);
    new_node->the_number_of_items = the_number_of_items;
    strcpy(new_node->name_of_client, head_of_client->name);
    strcpy(new_node->last_name, head_of_client->last_name);
    strcpy(new_node->adress_of_client, head_of_client->adress);
    strcpy(new_node->email, head_of_client->email);
    strcpy(new_node->phone, head_of_client->phone);
    strcpy(new_node->name_of_product, head_of_product->name);
    strcpy(new_node->category, head_of_product->category);
    new_node->price_of_product = head_of_product->price;
    new_node->product_id = head_of_product->id;
    new_node->total_price = (head_of_product->price*the_number_of_items);
    strcpy(new_node->status, status);
    strcpy(new_node->delivery_adress, delivery_adress);

    if (*head_of_orders == NULL)
    {
        *head_of_orders = new_node;
        new_node->next = NULL;
        printf("Order inserted successfully\n");
        Sleep(2000);
        system("cls");
        return;
    }
    list_of_orders* curr_order = *head_of_orders;
    while (curr_order->next != NULL)
    {
        curr_order = curr_order->next;
    }
    curr_order->next = new_node;
    new_node->next = NULL;
    printf("Order inserted successfully\n");
    Sleep(2000);
    system("cls");
    return;
}
void list_add_order (list_of_orders **head_of_orders, int order_id, int product_id, int the_number_of_items, char *name_of_client, char *last_name, char *adress_of_client, char *email, char *phone, char *name_of_product, char *category, char *delivery_adress, char *date_of_submission, char *status, float price_of_product, float total_price)
{
    list_of_orders* new_node = (list_of_orders*)malloc(sizeof(list_of_orders));
    if (new_node == NULL)
    {
        exit(5);
    }
    new_node->order_id = order_id;
    strcpy(new_node->date_of_submission, date_of_submission);
    new_node->the_number_of_items = the_number_of_items;
    strcpy(new_node->name_of_client, name_of_client);
    strcpy(new_node->last_name, last_name);
    strcpy(new_node->adress_of_client, adress_of_client);
    strcpy(new_node->email, email);
    strcpy(new_node->phone, phone);
    strcpy(new_node->name_of_product, name_of_product);
    strcpy(new_node->category, category);
    new_node->price_of_product = price_of_product;
    new_node->product_id = product_id;
    new_node->total_price = (price_of_product * the_number_of_items);
    strcpy(new_node->status, status);
    strcpy(new_node->delivery_adress, delivery_adress);
    if (*head_of_orders == NULL)
    {
        *head_of_orders = new_node;
        new_node->next = NULL;
        return;
    }
    list_of_orders* tmp = *head_of_orders;
    while (tmp->next != NULL)
    {
        tmp = tmp->next;
    }
    tmp->next = new_node;
    new_node->next = NULL;
    return;
}
void load_order(const char *fn3, list_of_orders **head_of_orders)
{
    FILE* f3 = fopen(fn3,"r");
    if (f3==NULL)
    {
        printf("Eror: cant open file");
        return;
    }
    int order_id, the_number_of_items, product_id;
    float price_of_product, total_price;
    char date_of_submission[N], delivery_adress[N], status[N], name_of_client[N], last_name[N], adress_of_client[N], email[N], phone[N], name_of_product[N], category[N];
    list_of_orders** curr = head_of_orders;
    while (fscanf(f3,"%d%d%d%s%s%s%s%s%s%s%s%s%s%f%f", &order_id, &product_id, &the_number_of_items, name_of_client, last_name, adress_of_client, email, phone, name_of_product, category, delivery_adress, date_of_submission, status, &price_of_product, &total_price) == 15)
    {
        list_add_order(curr, order_id, product_id, the_number_of_items, name_of_client, last_name, adress_of_client, email, phone, name_of_product, category, delivery_adress, date_of_submission, status, price_of_product, total_price);
    }
    fclose(f3);

    return;
}
void list_of_order_print (list_of_orders* head_of_order)
{
    int count=1;
    printf("List elements:\n");
    if (head_of_order == NULL)
    {
        printf("List is empty\n");
        return;
    }
    while (head_of_order != NULL)
    {
        printf("Element: %d\n\nCustomer data:\nName - %s\nSurname - %s\nAdress - %s\nEmail - %s\nPhone number - %s\n\nProduct data:\nid - %d\nname - %s\nCategory - %s\nPrice - %.2f\n\nOrder data:\nId - %d\nDate of submission - %s\nDelivery adress - %s\nStatus - %s\nNumber of items of the product purchased - %d\nTotal price - %.2f\n\n", count, head_of_order->name_of_client, head_of_order->last_name, head_of_order->adress_of_client, head_of_order->email, head_of_order->phone, head_of_order->product_id, head_of_order->name_of_product, head_of_order->category, head_of_order->price_of_product, head_of_order->order_id, head_of_order->date_of_submission, head_of_order->delivery_adress, head_of_order->status, head_of_order->the_number_of_items, head_of_order->total_price);
        Break();
        head_of_order = head_of_order->next;
        count++;
    }
    return;
}
void search_order (list_of_orders* head_of_orders, int id)
{
    int count = 1;
    if (head_of_orders == NULL)
    {
        printf("List is empty\n");
        Sleep(2000);
        system("cls");
        return;
    }
    while (head_of_orders != NULL)
    {
        if (head_of_orders->order_id == id)
        {
            printf("Element: %d\n\nCustomer data:\nName - %s\nSurname - %s\nAdress - %s\nEmail - %s\nPhone number - %s\n\nProduct data:\nid - %d\nname - %s\nCategory - %s\nPrice - %.2f\n\nOrder data:\nId - %d\nDate of submission - %s\nDelivery adress - %s\nStatus - %s\nNumber of items of the product purchased - %d\nTotal price - %.2f\n\n", count, head_of_orders->name_of_client, head_of_orders->last_name, head_of_orders->adress_of_client, head_of_orders->email, head_of_orders->phone, head_of_orders->product_id, head_of_orders->name_of_product, head_of_orders->category, head_of_orders->price_of_product, head_of_orders->order_id, head_of_orders->date_of_submission, head_of_orders->delivery_adress, head_of_orders->status, head_of_orders->the_number_of_items, head_of_orders->total_price);
            return;
        }
        head_of_orders = head_of_orders->next;
        count++;
    }
    printf("The order with the given id is not on the list\n");
    Sleep(3000);
    system("cls");
    return;
}
int check_if_id_of_order_appears (list_of_orders* head_of_orders, int id)
{
    if (head_of_orders == NULL)
    {
        return 0;
    }
    while (head_of_orders != NULL)
    {
        if (head_of_orders->order_id == id)
        {
            return 1;
        }
        head_of_orders = head_of_orders->next;
    }
    return 0;
}
int check_if_id_of_product_appears (list_of_product* head_of_product, int id)
{
    if (head_of_product == NULL)
    {
        return 0;
    }
    while (head_of_product != NULL)
    {
        if (head_of_product->id == id)
        {
            return 1;
        }
        head_of_product = head_of_product->next;
    }
    return 0;
}
void change_status (list_of_orders* head_of_orders, int id, char *status)
{
    if (head_of_orders == NULL)
    {
        printf("List is empty\n");
        Sleep(2000);
        system("cls");
        return;
    }
    while (head_of_orders != NULL)
    {
        if (head_of_orders->order_id == id)
        {
            strcpy(head_of_orders->status, status);
            printf("Successful order status change\n");
            Sleep(2000);
            system("cls");
            return;
        }
        head_of_orders = head_of_orders->next;
    }
    printf("The order with the given id is not on the list\n");
    Sleep(3000);
    system("cls");
    return;
}
void print_orders_with_same_client (list_of_orders* head_of_order, char *name, char *surname)
{
    if (head_of_order == NULL)
    {
        printf("List is empty\n");
        return;
    }
    int count = 1;
    while (head_of_order != NULL)
    {
        if (strcmp(head_of_order->name_of_client, name) == 0 && strcmp(head_of_order->last_name, surname) == 0)
        {
            printf("Element: %d\n\nCustomer data:\nName - %s\nSurname - %s\nAdress - %s\nEmail - %s\nPhone number - %s\n\nProduct data:\nid - %d\nname - %s\nCategory - %s\nPrice - %.2f\n\nOrder data:\nId - %d\nDate of submission - %s\nDelivery adress - %s\nStatus - %s\nNumber of items of the product purchased - %d\nTotal price - %.2f\n\n", count, head_of_order->name_of_client, head_of_order->last_name, head_of_order->adress_of_client, head_of_order->email, head_of_order->phone, head_of_order->product_id, head_of_order->name_of_product, head_of_order->category, head_of_order->price_of_product, head_of_order->order_id, head_of_order->date_of_submission, head_of_order->delivery_adress, head_of_order->status, head_of_order->the_number_of_items, head_of_order->total_price);
            Break();
        }
        count++;
        head_of_order = head_of_order->next;
    }
}
void print_orders_with_same_product (list_of_orders* head_of_order, int product_id)
{
    int check_if=0;
    if (head_of_order == NULL)
    {
        printf("List is empty\n");
        return;
    }
    int count = 1;
    while (head_of_order != NULL)
    {
        if (head_of_order->product_id == product_id)
        {
            printf("Element: %d\n\nCustomer data:\nName - %s\nSurname - %s\nAdress - %s\nEmail - %s\nPhone number - %s\n\nProduct data:\nid - %d\nname - %s\nCategory - %s\nPrice - %.2f\n\nOrder data:\nId - %d\nDate of submission - %s\nDelivery adress - %s\nStatus - %s\nNumber of items of the product purchased - %d\nTotal price - %.2f\n\n", count, head_of_order->name_of_client, head_of_order->last_name, head_of_order->adress_of_client, head_of_order->email, head_of_order->phone, head_of_order->product_id, head_of_order->name_of_product, head_of_order->category, head_of_order->price_of_product, head_of_order->order_id, head_of_order->date_of_submission, head_of_order->delivery_adress, head_of_order->status, head_of_order->the_number_of_items, head_of_order->total_price);
            Break();
            check_if++;
        }
        count++;
        head_of_order = head_of_order->next;
    }
    if (check_if == 0)
    {
        printf("There are no orders for the product with the given id\n");
        return;
    }

}
void deallocate_orders (list_of_orders **head_of_orders)
{
    list_of_orders* curr = *head_of_orders;
    while (curr != NULL)
    {
        list_of_orders* tmp = curr;
        curr = curr->next;
        free(tmp);
    }
    *head_of_orders = NULL;
    return;
}
int main()
{
    char clients[12]="klienci.txt";
    char products[13]="produkty.txt";
    char orders[15]="zamowienia.txt";
    char status_sent[5]="sent";
    char status_canceled[9]="canceled";

    list_of_client* head1 = NULL;
    list_of_product* head2 = NULL;
    list_of_orders* head3 = NULL;

    load_client(clients, &head1);
    load_product(products, &head2);
    load_order(orders, &head3);

    int choose_status=0, go=1, database=0, operation=0, number=0, number_of_customer=0, number_of_product=0, order_id, number_of_items=0, client_re_operation=1, change_list=1, product_re_operation=1, order_re_operation=1;
    char name[N], last_name[N], adress[N], email[N], phone_number[N], date_of_shipment[N], shipment_adress[N];

    int id, order_operation=0;
    char name_of_product[N], category[N], go_min[N];
    float price;
    printf("If you want to open shop data base press any button on the keyboard\n");
    scanf("%s", &go_min);
    if (go == 1)
    {
        while (change_list == 1)
        {
            client_re_operation = 1;
            order_re_operation = 1;
            product_re_operation = 1;
            system("cls");
            printf("What database do you want to operate on?\n1 - clients\n2 - products\n3 - orders\n");
            scanf("%d", &database);
            if (database == 1)
            {
                system("cls");
                while (client_re_operation == 1)
                {
                    system("cls");
                    printf("What kind of operation do you want to process?\n1 - show list\n2 - add new element\n3 - remove client\n4 - search client\n5 - edit client\n6 - save and exit\n7 - exit program\n8 - return to your choice list\n");
                    scanf("%d", &operation);
                    system("cls");
                    switch (operation)
                    {
                    case 1:
                        list_of_clients_print(head1);
                        printf("\n");
                        break;
                    case 2:
                        printf("Provide the attributes in the order given:\nname\nsurname\naddress\nemail\ntelephone number\n");
                        scanf("%s %s %s %s %s", name, last_name, adress, email, phone_number);
                        system("cls");
                        list_add_client(&head1, name, last_name, adress, email, phone_number);
                        printf("Client loaded correctly\n");
                        Sleep(2000);
                        system("cls");
                        break;
                    case 3:
                        list_of_clients_print(head1);
                        printf("Enter the customer list node number that you want to delete (counting from 1)\n");
                        scanf("%d", &number);
                        system("cls");
                        remove_client(&head1, number);
                        break;
                    case 4:
                        printf("Enter in the order given: name and surname of the customer you want to search\n");
                        scanf("%s %s", name, last_name);
                        system("cls");
                        printf("\n");
                        search_client (head1, name, last_name);
                        printf("\n");
                        break;
                    case 5:
                        list_of_clients_print(head1);
                        printf("\n");
                        printf("Enter the number of the list node you want to edit and enter the parameters to replace the current one in the given order:\nname\nsurname\nadress\ne-mail\nphone number\n");
                        scanf("%d %s %s %s %s %s", &number, name, last_name, adress, email, phone_number);
                        system("cls");
                        edit_client(&head1, number, name, last_name, adress, email, phone_number);
                        break;
                    case 6:
                        save_list_of_client_to_file(head1, clients);
                        deallocate_clients(&head1);
                        exit(10);
                        break;
                    case 7:
                        deallocate_clients(&head1);
                        exit(0);
                        break;
                    case 8:
                        client_re_operation = 2;
                        break;
                    default:
                        printf("Choose 1 of given options (1-7)\n");
                        Sleep(2000);
                        break;
                    }
                    if (client_re_operation == 1)
                    {
                        printf("Do you want to return to the operation selection?\n1 - Yes\n2 - No (exit program)\n");
                        scanf("%d", &client_re_operation);
                        if (client_re_operation == 2)
                        {
                            deallocate_clients(&head1);
                            exit(0);
                        }
                    }
                }
            }
            if (database == 2)
            {
                system("cls");
                while (product_re_operation == 1)
                {
                    system("cls");
                    printf("What kind of operation do you want to process?\n1 - show list\n2 - add new element\n3 - remove product\n4 - search product\n5 - edit product\n6 - save and exit\n7 - exit program\n8 - return to the choice list\n");
                    scanf("%d", &operation);
                    system("cls");
                    switch (operation)
                    {
                    case 1:
                        list_of_products_print(head2);
                        printf("\n");
                        break;
                    case 2:
                        printf("Provide the attributes in the order given:\nid\nname of product\ncategory\nprice\n\n");
                        scanf("%d %s %s %f", &id, name_of_product, category, &price);
                        if (check_if_id_of_product_appears(head2, id) == 0)
                        {
                            system("cls");
                            list_add_product(&head2, id, name_of_product, category, price);
                            printf("Product loaded succesfully\n");
                            Sleep(2000);
                            system("cls");
                            break;
                        }
                        else
                        {
                            printf("Id number you gave, appears on list, you must enter unique number\n");
                            Sleep(2000);
                            system("cls");
                            break;
                        }
                    case 3:
                        list_of_products_print(head2);
                        printf("\n");
                        printf("Enter the product list node number that you want to delete (counting from 1)\n");
                        scanf("%d", &number);
                        system("cls");
                        remove_product(&head2, number);
                        break;
                    case 4:
                        list_of_products_print(head2);
                        printf("\n");
                        printf("Enter name of the product you want to search\n");
                        scanf("%s", name);
                        system("cls");
                        search_product(head2, name);
                        break;
                    case 5:
                        list_of_products_print(head2);
                        printf("\n");
                        printf("Enter the number of the list node you want to edit and enter the parameters to replace the current one in the given order:\nid\nname\ncategory\nprice\n");
                        scanf("%d %d %s %s %f", &number, &id, name, category, &price);
                        if (check_if_id_of_product_appears(head2, id) == 1)
                        {
                            system("cls");
                            printf("The id you entered already exist\n");
                            Sleep(2000);
                            system("cls");
                            break;
                        }
                        system("cls");
                        edit_product(&head2, number, id, name, category, price);
                        list_of_products_print(head2);
                        break;
                    case 6:
                        save_list_of_product_to_file(head2, products);
                        deallocate_product(&head2);
                        exit(10);
                        break;
                    case 7:
                        deallocate_product(&head2);
                        exit(0);
                        break;
                    case 8:
                        product_re_operation = 2;
                        break;
                    default:
                        printf("Choose 1 of given options (1-7)\n");
                        Sleep(2000);
                        system("cls");
                        break;
                    }
                    if (product_re_operation == 1)
                    {
                        printf("Do you want to return to the operation selection?\n1 - Yes\n2 - No (exit program)\n");
                        scanf("%d", &product_re_operation);
                        if (product_re_operation == 2)
                        {
                            deallocate_product(&head2);
                            exit(0);
                        }
                    }
                }
            }
            if (database == 3)
            {
                system("cls");
                while (order_re_operation == 1)
                {
                    system("cls");
                    printf("What kind of operation do you want to process?\n1 - show list\n2 - add new order\n3 - remove order\n4 - search order\n5 - change status of order\n6 - search for orders placed by a given customer\n7 - search for orders placed by a given product\n8 - save and exit\n9 - exit\n10 - return to the choice list\n");
                    scanf("%d", &order_operation);
                    system("cls");
                    switch (order_operation)
                    {
                    case 1:
                        list_of_order_print(head3);
                        printf("\n");
                        break;
                    case 2:
                        printf("Provide the attributes in the order given:\nnumber of the customer placing the order\nproduct number\norder ID\nnumber of items\ndate of shipment\ndelivery address\n");
                        scanf("%d %d %d %d %s %s", &number_of_customer, &number_of_product, &order_id, &number_of_items, date_of_shipment, shipment_adress);
                        system("cls");
                        while (check_if_id_of_order_appears(head3, order_id)==1)
                        {
                            printf("Please enter an id that is not in the orders\n");
                            scanf("%d", &order_id);
                            system("cls");
                        }
                        insert_order(&head3, head1, head2, number_of_customer, number_of_product, order_id, number_of_items, date_of_shipment, shipment_adress);
                        break;
                    case 3:
                        printf("Enter the customer list node number that you want to delete (counting from 1)\n");
                        scanf("%d", &number);
                        system("cls");
                        remove_order(&head3, number);
                        break;
                    case 4:
                        printf("Enter the ID of the order you would like to search\n");
                        scanf("%d", &order_id);
                        system("cls");
                        search_order(head3, order_id);
                        break;
                    case 5:
                        list_of_order_print(head3);
                        printf("\n");
                        printf("Enter the id of the order you want to change the order status\n");
                        scanf("%d", &order_id);
                        while (check_if_id_of_order_appears (head3, order_id) == 0)
                        {
                            system("cls");
                            list_of_order_print(head3);
                            printf("\n");
                            printf("The order id provided by you is not on the list, please enter the id of an existing order\n");
                            scanf("%d", &order_id);
                        }
                        system("cls");
                        printf("Select the status you want to set\n1 - sent\n2 - canceled\n");
                        scanf("%d", &choose_status);
                        system("cls");
                        while (choose_status != 1 && choose_status != 2)
                        {
                            printf("Select the status you want to set\n1 - sent\n2 - canceled\n\n");
                            printf("Enter correct answer (1 or 2)\n");
                            scanf("%d", &choose_status);
                            system("cls");
                        }
                        if (choose_status == 1)
                        {
                            change_status (head3, order_id, status_sent);
                            break;
                        }
                        else if (choose_status == 2)
                        {
                            change_status (head3, order_id, status_canceled);
                            break;
                        }
                    case 6:
                        list_of_clients_print (head1);
                        printf("Provide the customer's name and surname in the order given\n");
                        scanf("%s%s", name, last_name);
                        system("cls");
                        print_orders_with_same_client(head3, name, last_name);
                        break;
                    case 7:
                        list_of_products_print(head2);
                        printf("Provide product id\n");
                        scanf("%d", &id);
                        system("cls");
                        print_orders_with_same_product(head3, id);
                        break;
                    case 8:
                        save_list_of_order_to_file(orders, head3);
                        deallocate_orders (&head3);
                        exit(10);
                        break;
                    case 9:
                        deallocate_orders (&head3);
                        exit(0);
                        break;
                    case 10:
                        order_re_operation = 2;
                        break;
                    default:
                        printf("Choose 1 of given options (1-9)\n");
                        Sleep(2000);
                        break;
                    }
                    if (order_re_operation == 1)
                    {
                        printf("Do you want to return to the operation selection?\n1 - Yes\n2 - No (exit program)\n");
                        scanf("%d", &order_re_operation);
                        if (order_re_operation == 2)
                        {
                            deallocate_orders(&head3);
                            exit(0);
                        }
                    }
                }
            }
            if (database != 1 && database != 2 && database != 3)
            {
                printf("you must enter a number belonging to (1-3)\n");
                Sleep(2000);
            }
        }
    }
    deallocate_clients(&head1);
    deallocate_product(&head2);
    deallocate_orders (&head3);
    return 0;
}
