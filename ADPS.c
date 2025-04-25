/* Module: TU858/1 - CMPU1001 Algorithm Design and Problem Solving CA Project

This program is a simulation and development of a car parts firm’s order management system, providing a menu-driven interface for efficient product management. It initialises sample test data, reads data from the array, and sorts all product data by weight (from lightest to heaviest) using merge sort. It also allows adding, deleting, and updating product information, it searches for a product by weight using binary search, and generates a summary of the delivery docket (document listing content) information. All while focusing on efficient data processing, delivery generation, and user-friendly interaction.

Author: C24329646 - Lívia Ferreira Guimaraes Neves
Date: 25/04/2025 */

// standard input output functions
#include <stdio.h>
// built-in string functions
#include <string.h>
// built-in functions to convert strings into their equivalent numeric value
#include <stdlib.h>

// macros/symbolic names defining size
#define SIZE 100 // size of the string
#define QUANTITY_OF_PRODUCTS 48 // number of products in the initial list
#define MAX_PRODUCTS 100 // maximum number of products allowed



// structure template to store date
struct date
{
    int day; // day of the month
    int month; // month of the year
    int year; // year
};

// structure template to store time
struct time
{
    int hour; // hour of the day
    int minute; // minute of the hour
};

// structure template to store data of company’s order management system
struct order_management_data
{
    int line_Code; // line code (numeric)
    int batch_Code; // batch code (numeric)
    struct date batch_Date; // batch date – numbered for day, month, and year
    struct time batch_Time; // batch time– numbered for hour of day, and minute of hour
    int product_Id; // product ID (numeric)
    char product_Name[SIZE]; // product name (text)
    char target_Engine_Code[SIZE]; // target engine code (text)
    int team_Number; // team number (numeric)
    int bin_Number; // bin number (numeric)
    float weight; // weight of the product (numeric)
    float price; // price of the product (numeric)
};



// function calls

// function to initialise the array with sample product data to be tested - function calls array of structure which contains stored data
void initialise_test_data(struct order_management_data records[]);

// function to sort the array of product data by weight - function calls array of structure which contains stored data, pointer to integer that stores the size/number of products of the array
void sort_data_by_weight(struct order_management_data records[], int size);

// function to print the full product list in the array - function calls array of structure which contains stored data, pointer to integer that stores the size/number of products of the array
void print_product_list(struct order_management_data records[], int size);

// function to add a new product to the array - function calls array of structure which contains stored data, pointer to integer that stores the size/number of products of the array
void add_product(struct order_management_data records[], int *size);

// function to delete a product from the array based on its product IDs - function calls array of structure which contains stored data, pointer to integer that stores the size/number of products of the array
void delete_product(struct order_management_data records[], int *size);

// function to update existing product information in the array - function calls array of structure which contains stored data, pointer to integer that stores the size/number of products of the array
void update_product(struct order_management_data records[], int size);

// function to execute a binary search to find a product by weight - function calls array of structure which contains stored data, pointer to integer that stores the size/number of products of the array, and float variable that stores the target weight
int binary_search_by_weight(struct order_management_data records[], int size, float target_weight);

// function to summarise the total delivery information (weight and price of all products in the array) - function calls array of structure which contains stored data, pointer to integer that stores the size/number of products of the array
void summarise_delivery(struct order_management_data records[], int size);

// function to display the menu options
void display_menu();

// function to merge two subarrays
void merge(struct order_management_data records[], int left, int mid, int right);

// function to perform merge sort
void merge_sort(struct order_management_data records[], int left, int right);



// main function
int main() 
{
    struct order_management_data records[MAX_PRODUCTS]; // array to store product records
    int size = 0; // variable to track the number of products
    int choice; // variable to store user choice

    // initialise test data
    initialise_test_data(records);
    // set size to the number of initialised products
    size = QUANTITY_OF_PRODUCTS;

    // sort all data records by weight
    sort_data_by_weight(records, size);

    // infinite loop to keep the program running until the user chooses to exit
    int running = 1; // variable to control the loop

    while (running)
    {
        display_menu(); // display the menu options
        printf("Enter your choice: "); // prompt for user choice
        scanf("%d", &choice); // read user choice
    
        if (choice == 1)
        {
            print_product_list(records, size); // display product list
        } else if (choice == 2)
        {
            add_product(records, &size); // add new product
        } else if (choice == 3)
        {
            delete_product(records, &size); // delete product
        } else if (choice == 4)
        {
            update_product(records, size); // update product information
        } else if (choice == 5)
        {
            float target_weight;
    
            printf("Enter weight to search: ");
            scanf("%f", &target_weight); // Read input directly as a float
    
            int index = binary_search_by_weight(records, size, target_weight);
            if (index != -1)
            {
                printf("Product found: %s\n", records[index].product_Name);
            } else
            {
                printf("Product not found.\n");
            }
        } else if (choice == 6)
        {
            summarise_delivery(records, size); // summarise delivery
        } else if (choice == 0)
        {
            printf("Exiting the program.\n"); // exit message
            running = 0; // set running to 0 to exit the loop
        } else
        {
            printf("Invalid choice. Please try again.\n"); // invalid choice message
        }
    }

    return 0; // return statement indicating successful execution
} // end main function



// function to initialise test data
void initialise_test_data(struct order_management_data records[])
{
    // product data for team 1
    records[0] = (struct order_management_data){6001, 2001, {1, 4, 2025}, {10, 30}, 12025, "Brake Pads Set (Front)", "LIV01", 1, 5001, 1.8, 55.0};
    records[1] = (struct order_management_data){6002, 2002, {2, 4, 2025}, {10, 35}, 22025, "Engine Oil 5W-30 (5L)", "LIV02", 1, 5002, 4.5, 59.0};
    records[2] = (struct order_management_data){6003, 2003, {3, 4, 2025}, {10, 50}, 32025, "Car Battery (12V, 60Ah)", "LIV03", 1, 5003, 17.2, 140.0};
    records[3] = (struct order_management_data){6004, 2004, {4, 4, 2025}, {14, 20}, 42025, "Radiator", "LIV04", 1, 5004, 9.1, 180.0};
    records[4] = (struct order_management_data){6005, 2005, {5, 4, 2025}, {15, 50}, 52025, "Fuel Pump", "LIV05", 1, 5005, 1.8, 120.0};
    records[5] = (struct order_management_data){6006, 2006, {6, 4, 2025}, {16, 10}, 62025, "Alternator", "LIV06", 1, 5006, 5.4, 175.0};
    records[6] = (struct order_management_data){6007, 2007, {7, 4, 2025}, {18, 45}, 72025, "Air Filter", "LIV07", 1, 5007, 0.7, 22.0};
    records[7] = (struct order_management_data){6008, 2008, {8, 4, 2025}, {19, 15}, 82025, "Headlight Assembly (1 piece)", "LIV08", 1, 5008, 2.7, 130.0};
    records[8] = (struct order_management_data){6009, 2009, {9, 4, 2025}, {19, 40}, 92025, "Shock Absorber (1 piece)", "LIV09", 1, 5009, 3.2, 80.0};
    records[9] = (struct order_management_data){6010, 2010, {10, 4, 2025}, {20, 5}, 102025, "Timing Belt", "LIV10", 1, 5010, 0.7, 60.0};
    records[10] = (struct order_management_data){6011, 2011, {11, 4, 2025}, {21, 30}, 112025, "Spark Plug Set (4 pieces)", "LIV11", 1, 5011, 0.45, 25.0};
    records[11] = (struct order_management_data){6012, 2012, {12, 4, 2025}, {23, 45}, 122025, "Muffler", "LIV12", 1, 5012, 0.45, 25.0};

    // product data for team 2
    records[12] = (struct order_management_data){6013, 2013, {13, 4, 2025}, {2, 50}, 132025, "Brake Fluid", "LIV13", 2, 5013, 1.0, 15.0};
    records[13] = (struct order_management_data){6014, 2014 , {14, 4, 2025}, {4, 15}, 142025, "Transmission Fluid", "LIV14", 2, 5014, 1.5, 18.0};
    records[14] = (struct order_management_data){6015, 2015, {15, 4, 2025}, {5, 45}, 152025, "Brake Rotor", "LIV15", 2, 5015, 5.0, 75.0};
    records[15] = (struct order_management_data){6016, 2016, {16, 4, 2025}, {6, 30}, 162025, "Fuel Filter", "LIV16", 2, 5016, 0.3, 20.0};
    records[16] = (struct order_management_data){6017, 2017, {17, 4, 2025}, {7, 15}, 172025, "Power Steering Fluid", "LIV17", 2, 5017, 1.2, 22.0};
    records[17] = (struct order_management_data){6018, 2018, {18, 4, 2025}, {8, 0}, 182025, "Differential Fluid", "LIV18", 2, 5018, 1.8, 30.0};
    records[18] = (struct order_management_data){6019, 2019, {19, 4, 2025}, {9, 45}, 192025, "Brake Caliper", "LIV19", 2, 5019, 2.5, 90.0}; 
    records[19] = (struct order_management_data){6020, 2020, {20, 4, 2025}, {10, 10}, 202025, "Fuel Pump Relay", "LIV20", 2, 5020, 0.1, 10.0};
    records[20] = (struct order_management_data){6021, 2021, {21, 4, 2025}, {11, 15}, 212025, "Ignition Switch", "LIV21", 2, 5021, 0.2, 35.0};
    records[21] = (struct order_management_data){6022, 2022, {22, 4, 2025}, {12, 25}, 222025, "Starter Motor", "LIV22", 2, 5022, 3.0, 150.0};
    records[22] = (struct order_management_data){6023, 2023, {23, 4, 2025}, {13, 45}, 232025, "Alternator Belt", "LIV23", 2, 5023, 0.5, 25.0};
    records[23] = (struct order_management_data){6024, 2024, {24, 4, 2025}, {14, 30}, 242025, "Timing Chain", "LIV24", 2, 5024, 1.0, 40.0};

    // product data for team 3
    records[24] = (struct order_management_data){6025, 2025, {25, 4, 2025}, {15, 15}, 252025, "Exhaust Pipe", "LIV25", 3, 5025, 2.0, 60.0};
    records[25] = (struct order_management_data){6026, 2026, {26, 4, 2025}, {16, 0}, 262025, "Catalytic Converter", "LIV26", 3, 5026, 3.5, 200.0};
    records[26] = (struct order_management_data){6027, 2027, {27, 4, 2025}, {17, 45}, 272025, "Oxygen Sensor", "LIV27", 3, 5027, 0.3, 50.0};
    records[27] = (struct order_management_data){6028, 2028, {28, 4, 2025}, {18, 30}, 282025, "Mass Air Flow Sensor", "LIV28", 3, 5028, 0.4, 70.0};
    records[28] = (struct order_management_data){6029, 2029, {29, 4, 2025}, {19, 15}, 292025, "Throttle Position Sensor", "LIV29", 3, 5029, 0.5, 45.0};
    records[29] = (struct order_management_data){6030, 2030, {30, 4, 2025}, {20, 55}, 302025, "Camshaft Position Sensor", "LIV30", 3, 5030, 0.6, 55.0};
    records[30] = (struct order_management_data){6031, 2031, {1, 5, 2025}, {21, 45}, 312025, "Fuel Pressure Regulator", "LIV31", 3, 5031, 0.7, 65.0};
    records[31] = (struct order_management_data){6032, 2032, {2, 5, 2025}, {0, 30}, 322025, "Engine Control Module", "LIV32", 3, 5032, 1.2, 300.0};
    records[32] = (struct order_management_data){6033, 2033, {3, 5, 2025}, {1, 15}, 332025, "Ignition Module", "LIV33", 3, 5033, 0.8, 80.0};
    records[33] = (struct order_management_data){6034, 2034, {4, 5, 2025}, {2, 15}, 342025, "Fuel Tank", "LIV34", 3, 5034, 5.0, 250.0};
    records[34] = (struct order_management_data){6035, 2035, {5, 5, 2025}, {2, 45}, 352025, "Radiator Cap", "LIV35", 3, 5035, 0.1, 10.0};
    records[35] = (struct order_management_data){6036, 2036, {6, 5, 2025}, {3, 30}, 362025, "Hoses and Clamps", "LIV36", 3, 5036, 0.5, 15.0};

    // product data for team 4
    records[36] = (struct order_management_data){6037, 2037, {7, 5, 2025}, {4, 15}, 372025, "Battery Terminal", "LIV37", 4, 5037, 0.2, 5.0};
    records[37] = (struct order_management_data){6038, 2038, {8, 5, 2025}, {5, 0}, 382025, "Fuses", "LIV38", 4, 5038, 0.05, 2.0};
    records[38] = (struct order_management_data){6039, 2039, {9, 5, 2025}, {5, 45}, 392025, "Wiring Harness", "LIV39", 4, 5039, 1.5, 100.0};
    records[39] = (struct order_management_data){6040, 2040, {10, 5, 2025}, {6, 30}, 402025, "Head Gasket", "LIV40", 4, 5040, 0.3, 45.0};
    records[40] = (struct order_management_data){6041, 2041, {11, 5, 2025}, {7, 15}, 412025, "Oil Cooler", "LIV41", 4, 5041, 2.1, 85.0};
    records[41] = (struct order_management_data){6042, 2042, {12, 5, 2025}, {8, 0}, 422025, "Exhaust Gas Temp Sensor", "LIV42", 4, 5042, 0.3, 37.0};
    records[42] = (struct order_management_data){6043, 2043, {13, 5, 2025}, {8, 45}, 432025, "Cabin Filter", "LIV43", 4, 5043, 0.3, 15.0};
    records[43] = (struct order_management_data){6044, 2044, {14, 5, 2025}, {9, 30}, 442025, "Fuel Tank Cap", "LIV44", 4, 5044, 0.2, 10.0};
    records[44] = (struct order_management_data){6045, 2045, {15, 5, 2025}, {10, 15}, 452025, "Brake Light Switch", "LIV45", 4, 5045, 0.1, 5.0};
    records[45] = (struct order_management_data){6046, 2046, {16, 5, 2025}, {11, 0}, 462025, "Clutch Master Cylinder", "LIV46", 4, 5046, 1.0, 75.0};
    records[46] = (struct order_management_data){6047, 2047, {17, 5, 2025}, {11, 45}, 472025, "Brake Master Cylinder", "LIV47", 4, 5047, 1.2, 85.0};
    records[47] = (struct order_management_data){6048, 2048, {18, 5, 2025}, {12, 30}, 482025, "Power Brake Booster", "LIV48", 4, 5048, 3.0, 150.0};
}

// function to merge two subarrays
void merge(struct order_management_data records[], int left, int mid, int right)
{
    int n1 = mid - left + 1; // size of the left subarray
    int n2 = right - mid; // size of the right subarray

    // temporary arrays to hold the left and right subarrays
    struct order_management_data L[n1], R[n2];

    // copy data to the left subarray
    for (int i = 0; i < n1; i++)
        L[i] = records[left + i];
    // copy data to the right subarray
    for (int j = 0; j < n2; j++)
        R[j] = records[mid + 1 + j];

    // initialize indices for left, right, and merged arrays
    int i = 0, j = 0, k = left;

    // merge the subarrays back into the original array
    while (i < n1 && j < n2) {
        if (L[i].weight <= R[j].weight) // compare weights of elements in left and right subarrays
            records[k++] = L[i++]; // copy the smaller element from the left subarray
        else
            records[k++] = R[j++]; // copy the smaller element from the right subarray
    }

    // copy any remaining elements from the left subarray
    while (i < n1)
        records[k++] = L[i++];

    // copy any remaining elements from the right subarray
    while (j < n2)
        records[k++] = R[j++];
}

// function to perform merge sort
void merge_sort(struct order_management_data records[], int left, int right)
{
    if (left < right)
    {
        // calculate the middle index of the array
        int mid = left + (right - left) / 2;

        // recursively sort the left subarray
        merge_sort(records, left, mid);

        // recursively sort the right subarray
        merge_sort(records, mid + 1, right);

        // merge the two sorted subarrays
        merge(records, left, mid, right);
    }
}

// function to sort the array of product data by weight
void sort_data_by_weight(struct order_management_data records[], int size)
{
    merge_sort(records, 0, size - 1); // call merge_sort on the entire array
}

// function to print the full product list in the array
void print_product_list(struct order_management_data records[], int size)
{
    printf("\n>>>>>> Product List <<<<<<\n"); // header for product list
    printf("--------------------------\n"); // separator

    // for loop to loop through each product in the records array
    for (int i = 0; i < size; i++)
    {
        // printing product details
        printf("Line Code: %d\n", records[i].line_Code); // printing line code
        printf("Batch Code: %d\n", records[i].batch_Code); // printing batch code
        printf("Batch Date: %02d/%02d/%04d\n", records[i].batch_Date.day, records[i].batch_Date.month, records[i].batch_Date.year); // printing batch date
        printf("Batch Time: %02d:%02d\n", records[i].batch_Time.hour, records[i].batch_Time.minute); // printing batch time
        printf("Product ID: %d\n", records[i].product_Id); // printing product ID
        printf("Product Name: %s\n", records[i].product_Name); // printing product name
        printf("Target Engine Code: %s\n", records[i].target_Engine_Code); // printing target engine code
        printf("Team Number: %d\n", records[i].team_Number); // printing team number
        printf("Bin Number: %d\n", records[i].bin_Number); // printing bin number
        printf("Weight: %.2f kg\n", records[i].weight); // printing product weight
        printf("Price: %.2f\n", records[i].price); // printing product price
        printf("--------------------------\n"); // separator
    }
}

// function to add a new product to the array
void add_product(struct order_management_data records[], int *size)
{
    // check if maximum product limit is reached
    if (*size >= MAX_PRODUCTS)
    { 
        printf("Unfortunately you cannot add more products since maximum limit was reached.\n"); // inform user
        return; // exit function
    }
    
    // create a new product variable
    struct order_management_data new_product;

    printf("Enter Line Code: "); // prompt for line code
    scanf("%d", &new_product.line_Code); // read line code

    printf("Enter Batch Code: "); // prompt for batch code
    scanf("%d", &new_product.batch_Code); // read batch code
    
    printf("Enter Batch Date (dd mm yyyy): "); // prompt for batch date
    scanf("%d %d %d", &new_product.batch_Date.day, &new_product.batch_Date.month, &new_product.batch_Date.year); // read batch date
    
    printf("Enter Batch Time (hh mm): "); // prompt for batch time
    scanf("%d %d", &new_product.batch_Time.hour, &new_product.batch_Time.minute); // read batch time
    
    printf("Enter Product ID: "); // prompt for product ID
    scanf("%d", &new_product.product_Id); // read product ID
    
    printf("Enter Product Name: "); // prompt for product name
    getchar(); // take the newline character left by previous scanf
    fgets(new_product.product_Name, SIZE, stdin); // read product name
    new_product.product_Name[strcspn(new_product.product_Name, "\n")] = 0; // remove newline character
    
    printf("Enter Target Engine Code: "); // prompt for target engine code
    fgets(new_product.target_Engine_Code, SIZE, stdin); // read target engine code
    new_product.target_Engine_Code[strcspn(new_product.target_Engine_Code, "\n")] = 0; // remove newline character
    
    printf("Enter Bin Number: "); // prompt for bin number
    scanf("%d", &new_product.bin_Number); // read bin number

    printf("Enter Team Number: "); // prompt for team number code
    scanf("%d", &new_product.line_Code); // read line code
    
    printf("Enter Weight (kg): "); // prompt for weight
    scanf("%f", &new_product.weight); // read weight
    
    printf("Enter Price: "); // prompt for price
    scanf("%f", &new_product.price); // read price
    
    records[*size] = new_product; // add new product to records
    (*size)++; // increment size
    printf("Product was successfully added!\n"); // confirm addition
}

// function to delete a product from the array based on its product IDs
void delete_product(struct order_management_data records[], int *size)
{
    // variable to hold product ID to delete
    int product_id;

    printf("Enter Product ID to delete: "); // prompt for product ID
    scanf("%d", &product_id); // read product ID

    // loop through products
    for (int i = 0; i < *size; i++)
    {
        // check if product ID matches
        if (records[i].product_Id == product_id)
        {
            // loop to shift products to remove the deleted product
            for (int j = i; j < *size - 1; j++)
            {
                // move next product up
                records[j] = records[j + 1];
            }
            // decrement size
            (*size)--;
            printf("Product deleted successfully!\n"); // confirm deletion
            return; // exit function
        }
    }
    printf("Unfortunately the product was not found!\n"); // inform user if not found
}

// function to update existing product information in the array
void update_product(struct order_management_data records[], int size)
{
    // variable to hold product ID to update
    int product_id;

    // prompt for product ID
    printf("Enter Product ID to update: ");
    scanf("%d", &product_id); // read product ID
    getchar(); // consume the newline character left by previous scanf

    // loop through products
    for (int i = 0; i < size; i++)
    {
        // check if product ID matches
        if (records[i].product_Id == product_id)
        {
            printf("Updating Product: %s\n", records[i].product_Name); // inform user of product being updated
            printf("Enter new Product Name: "); // prompt for new product name
            fgets(records[i].product_Name, SIZE, stdin); // read new product name
            records[i].product_Name[strcspn(records[i].product_Name, "\n")] = 0; // remove newline character
            printf("Enter new Weight (kg): "); // prompt for new weight
            scanf("%f", &records[i].weight); // read new weight
            getchar(); // consume the newline character left by previous scanf
            printf("Enter new Price: "); // prompt for new price
            scanf("%f", &records[i].price); // read new price
            getchar(); // consume the newline character left by previous scanf
            printf("Product updated successfully!\n"); // confirm update
            return; // exit function
        }
    }
    printf("Unfortunately the product was not found!\n"); // inform user if not found
}

// function to execute a binary search to find a product by weight
int binary_search_by_weight(struct order_management_data records[], int size, float target_weight)
{
    // initialise search boundaries
    int left = 0, right = size - 1;

    // loop until left pointer exceeds right pointer
    while (left <= right)
    {
        // calculate mid-point
        int mid = left + (right - left) / 2;
       
        // compare directly as floats
        if (records[mid].weight < target_weight)
        {
            return mid; // return index if found
        }
        if (records[mid].weight < target_weight)
        {
            left = mid + 1; // search in the right half
        } else
        {
            right = mid - 1; // search in the left half
        }
    }
    return -1; // return -1 if not found
}

// function to summarise the total delivery information (weight, price, and number of all products in the array)
void summarise_delivery(struct order_management_data records[], int size)
{
    float total_weight = 0.0, total_price = 0.0; // initialise totals
    int total_products = 0; // initialise product count

    // loop through all products in the array
    for (int i = 0; i < size; i++)
    {
        total_weight += records[i].weight; // accumulate weight
        total_price += records[i].price; // accumulate price
        total_products++; // count products
    }

    printf("\nTotal Products: %d products\n", total_products); // display total number of products
    printf("Total Weight: %.2f kg\n", total_weight); // display total weight
    printf("Total Price: %.2f\n", total_price); // display total price
}

// function to display the menu options
void display_menu()
{
    printf("\n>>>>>> Car Parts Order Management System <<<<<<\n"); // menu header
    printf("-----------------------------------------------\n"); // separator
    printf(">>>>>> MENU <<<<<<\n\n"); // menu title
    printf("1. Display Product List\n"); // option to display product list
    printf("2. Add New Product\n"); // option to add a new product
    printf("3. Delete Product\n"); // option to delete a product
    printf("4. Update Product\n"); // option to update product information
    printf("5. Search Product by Weight\n"); // option to search for a product by weight
    printf("6. Summarise Delivery\n"); // option to summarise delivery
    printf("0. Exit\n"); // option to exit the program
}