#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
using namespace std;
void darazheader();
void mainmenuheader();
void loginheader();
void adminheader();
void allsellerheader();
void feedbackheader();
void reportheader();
void customerheader();
void searchheader();
void purchaseproductheader();
void sellermenuheader();
void newaccountheader();
void addheader();
void updateheader();
void deletheader();
void viewheader();
void restockheader();
void lowStockheader();

int option;
string brandname[50], name[50], idnum[50], category[50], price[50];
int quantity[50];
int initialquantity[50];
int rows = 0;
int counter = 0;
string check;
string line;
fstream dataseller;
fstream loginseller;
void hardeffect()
{
    system("color 04");
    Sleep(1000);
    system("color 03");
}
void softeffect()
{
    system("color 02");
    Sleep(1000);
    system("color 03");
}
void localeffect()
{
    system("color 05");
    Sleep(1000);
    system("color 03");
}
void mainmenu()
{
    cout << "1. Admin portal" << endl;
    cout << "2. Customer portal" << endl;
    cout << "3. Seller portal" << endl;
    cout << "9. EXIT" << endl;
}
void filetoarray()
{
    rows = 0;
    dataseller.open("sellerdata.txt", ios::in);
    if (!dataseller)
    {
        cout << "----File not found----" << endl;
        hardeffect();
        return;
    }

    string line;
    while (getline(dataseller, line))
    {
        int comma = 0;
        brandname[rows] = name[rows] = idnum[rows] = category[rows] = price[rows] = "";
        quantity[rows] = 0;

        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == ',')
            {
                comma++;
            }
            else if (comma == 0)
            {
                brandname[rows] += line[i];
            }
            else if (comma == 1)
            {
                name[rows] += line[i];
            }
            else if (comma == 2)
            {
                category[rows] += line[i];
            }
            else if (comma == 3)
            {
                idnum[rows] += line[i];
            }
            else if (comma == 4)
            {
                quantity[rows] = quantity[rows] * 10 + (line[i]);
                initialquantity[i] = quantity[rows];
            }
            else if (comma == 5)
            {
                price[rows] += line[i];
            }
        }
        rows++;
    }
    dataseller.close();
}
void datatofile()
{
    dataseller.open("sellerdata.txt", ios::out);
    if (!dataseller)
    {
        cout << "Error: Could not open file for writing!" << endl;
        return;
    }

    for (int i = 0; i < rows; i++)
    {
        if (brandname[i] != "") // Avoid saving empty rows
        {
            dataseller << brandname[i] << ","
                       << name[i] << ","
                       << category[i] << ","
                       << idnum[i] << ","
                       << quantity[i] << ","
                       << price[i] << endl;
        }
    }

    dataseller.close();
}
bool checkidproduct()
{
    for (int i = 0; i < rows; i++)
    {
        if (idnum[i] == check)
        {
            return true; // Return true if the product ID already exists
        }
    }
    return false; // Return false if no duplicate ID is found
}

void addproducts()
{
    cout << "Enter the product ID: ";
    cin >> check;
    if (!checkidproduct())
    {
        cin.ignore();
        idnum[rows] = check;
        cout << "Enter the brand name: ";
        getline(cin, brandname[rows]);
        cout << "Enter the product name: ";
        getline(cin, name[rows]);
        cout << "Enter the product category: ";
        getline(cin, category[rows]);
        cout << "Enter the quantity: ";
        cin >> quantity[rows];
        cout << "Enter the price: ";
        cin >> price[rows];
        rows++;
        datatofile();
        cout << "----Product added successfully!----" << endl;
        softeffect();
    }
    else
    {
        cout << "----Product ID already exists!----" << endl;
        hardeffect();
    }
}
void updateproduct()
{
    string id;
    cout << "Enter the product ID to update: ";
    cin >> id;

    for (int i = 0; i < rows; i++)
    {
        if (idnum[i] == id)
        {
            cout << "Enter new brand name: ";
            cin.ignore();
            getline(cin, brandname[i]);
            cout << "Enter new product name: ";
            getline(cin, name[i]);
            cout << "Enter new product category: ";
            getline(cin, category[i]);
            cout << "Enter new quantity: ";
            cin >> quantity[i]; // Fixed from `quantity[rows]`
            cout << "Enter new price: ";
            cin >> price[i];
            datatofile();
            cout << "----Product updated successfully----" << endl;
            softeffect();
            return;
        }
    }
    cout << "----Product not found!----" << endl;
    hardeffect();
}

bool delproduct()
{
    string id;
    cout << "Enter the product ID to delete: ";
    cin >> id;

    for (int i = 0; i < rows; i++)
    {
        if (idnum[i] == id)
        {
            brandname[i] = "\0";
            name[i] = "\0";
            idnum[i] = "\0";
            category[i] = "\0";
            price[i] = "\0";
            rows--;
            datatofile();
            return true;
        }
    }
    return false;
}
void viewallproducts()
{
    if (rows == 0)
    {
        cout << "----No products available.----" << endl;
        hardeffect();
        return;
    }

    for (int i = 0; i < rows; i++)
    {
        cout << "Brand name: " << brandname[i] << endl;
        cout << "Product name: " << name[i] << endl;
        cout << "Category: " << category[i] << endl;
        cout << "Product ID: " << idnum[i] << endl;
        cout << "Quantity: " << quantity[i] << endl;
        cout << "Price: " << price[i] << endl;
        cout << "-------------------------" << endl;
    }
    getch();
}
void restockProduct2(int newStock)
{
    quantity[counter] += newStock;
}
void restockProduct()
{
    counter = 0;
    string id;
    int newStock;
    cout << "Enter the product ID to restock: ";
    cin >> id;

    for (int i = 0; i < rows; i++)
    {
        if (idnum[i] == id)
        {
            cout << "Current stock: " << quantity[i] << endl;
            cout << "Enter more quantity to add: ";
            cin >> newStock;
            counter = i;
            restockProduct2(newStock);

            datatofile();

            cout << "----Product restocked successfully!----" << endl;
            softeffect();
            return;
        }
    }
    cout << "----Product not found!----" << endl;
    hardeffect();
}

bool checklogin()
{
    string loginpass;
    loginseller.open("sellerlogindata.txt", ios::in);
    while (loginseller >> loginpass)
    {
        if (loginpass == check)
        {
            loginseller.close();
            return true;
        }
    }
    loginseller.close();
    return false;
}

bool sellerlogin()
{
    cout << "Enter password: ";
    cin >> check;
    if (checklogin())
    {
        cout << "----Login successful!----" << endl;
        softeffect();
        filetoarray();
        return true;
    }
    else
    {
        cout << "----Incorrect password!----" << endl;
        hardeffect();
        return false;
    }
}

void savepassword()
{
    loginseller.open("sellerlogindata.txt", ios::app);
    loginseller << endl
                << check;
    loginseller.close();
}

void createaccount()
{
    cout << "Enter a password for your account: ";
    cin >> check;
    savepassword();
    cout << "----Account created successfully!----" << endl;
    softeffect();
}
void searchproducts()
{
    counter = 0;
    cout << "Enter product name or category to search: ";
    cin.ignore();
    getline(cin, check);
    for (int i = 0; i < rows; i++)
    {
        if (check == category[i] || check == name[i])
        {
            cout << "Brand name: " << brandname[i] << endl;
            cout << "Product name: " << name[i] << endl;
            cout << "Category: " << category[i] << endl;
            cout << "Product ID: " << idnum[i] << endl;
            cout << "Quantity: " << quantity[i] << endl;
            cout << "Price: " << price[i] << endl;
            cout << "-------------------------" << endl;
            counter++;
        }
    }

    if (counter == 0)
    {
        cout << "----No products found----" << endl;
        hardeffect();
    }
    getch();
}
void purchaseproduct()
{
    string id, custid;
    cout << "Enter your customer identity number: ";
    cin >> custid;
    cout << "Enter the product ID you want to purchase: ";
    cin >> id;
    bool productfound = false;

    for (int i = 0; i < rows; i++)
    {
        if (idnum[i] == id)
        {
            productfound = true;
            if (quantity[i] > 0) // Check if stock is available
            {
                quantity[i]--; // Reduce stock
                datatofile();
                cout << "----Product purchased successfully!----" << endl;
                softeffect();
            }
            else
            {
                cout << "----Insufficient stock!----" << endl;
                hardeffect();
            }
            break;
        }
    }
    if (!productfound)
    {
        cout << "----Product ID not found!----" << endl;
        hardeffect();
    }
}

void lowStockalert()
{
    int threshold;
    cout << "Enter stock threshold: ";
    cin >> threshold;
    bool found = false;
    for (int i = 0; i < rows; i++)
    {
        if (quantity[i] < threshold)
        {
            cout << "Brand name: " << brandname[i] << endl;
            cout << "Product name: " << name[i] << endl;
            cout << "Product ID: " << idnum[i] << endl;
            cout << "Stock available: " << quantity[i] << endl;
            cout << "-------------------------" << endl;
            found = true;
        }
    }
    if (!found)
    {
        cout << "----All products are sufficiently stocked!----" << endl;
        softeffect();
    }
    getch();
}
void customerFeedback()
{
    string id, feedback;
    cout << "Enter product ID to leave feedback: ";
    cin >> id;
    for (int i = 0; i < rows; i++)
    {
        if (idnum[i] == id)
        {
            cout << "Enter your feedback: ";
            cin.ignore();
            getline(cin, feedback);
            fstream feedbackFile;
            feedbackFile.open("feedback.txt", ios::app);
            feedbackFile << "Product ID: " << id;
            feedbackFile << "Feedback: " << feedback << endl;
            feedbackFile << "-------------------------" << endl;
            feedbackFile.close();
            cout << "----Feedback recorded successfully!----" << endl;
            return;
        }
    }
    cout << "----Product not found!----" << endl;
    hardeffect();
}
void viewAllSellerAccounts()
{
    fstream sellerFile;
    sellerFile.open("sellerlogindata.txt", ios::in);
    string line;
    while (getline(sellerFile, line))
    {
        cout << "Seller Account: " << line << endl;
    }
    sellerFile.close();
    getch();
}
void viewCustomerFeedback()
{
    fstream feedbackFile;
    feedbackFile.open("feedback.txt", ios::in);
    string line;
    while (getline(feedbackFile, line))
    {
        cout << line << endl;
    }
    feedbackFile.close();
    getch();
}
void blockSellerAccount()
{
    string sellerID;
    cout << "Enter seller ID to block: ";
    cin >> sellerID;
}
bool checkadmin(string pass, string email)
{
    string p, e;
    fstream admin;
    admin.open("adminlogin.txt", ios::in);
    while (admin >> p >> e)
    {
        if (pass == p && email == e)
        {
            admin.close();
            return true;
        }
    }
    return false;
    admin.close();
}
bool adminlogin()
{
    // system("cls");
    string pass, email;
    cout << "Enter your password: ";
    cin >> pass;
    cout << "Enter email: ";
    cin >> email;
    return checkadmin(pass, email);
}
void salesreport()
{
    int totalSold = 0;
    float totalEarnings = 0;
    cout << "Enter ID number for Report: ";
    string n;
    cin >> n;
    for (int i = 0; i < rows; i++)
    {
        if (n == idnum[i])
        {
            int sold;
            sold = initialquantity[i] - quantity[i];
            float priceValue = stof(price[i]); // Convert string to float using stof
            float earnings = sold * priceValue;
            totalSold += sold;
            totalEarnings += earnings;
        }
    }
    if (totalSold != 0)
    {
        cout << "TOTAL SOLD: " << totalSold << endl;
        cout << "TOTAL EARNINGS: " << totalEarnings << " PKR" << endl;
    }
    getch();
}
void colors()
{
    system("color 05");
    Sleep(200);
    system("color 06");
    Sleep(200);
    system("color 02");
    Sleep(200);
    system("color 04");
    Sleep(200);
    system("color 01");
    Sleep(200);
    system("color 02");
    Sleep(200);
    system("color 03");
    Sleep(200);
}
int main()
{
    filetoarray();
    system("cls");
    darazheader();
    colors();
    while (true)
    {
        system("color 03");
        system("cls");
        mainmenuheader();
        mainmenu();
        cin >> option;
        if (option == 1)
        {
            system("cls");
            loginheader();
            if (adminlogin())
            {
                while (true)
                {
                    system("cls");
                    adminheader();
                    cout << "1. View all seller accounts" << endl;
                    cout << "2. View all feed backs of customers" << endl;
                    cout << "3. Block a seller" << endl;
                    cout << "4. sales report" << endl;
                    cout << "6. Back to main menu" << endl;
                    cin >> option;
                    if (option == 1)
                    {
                        system("cls");
                        allsellerheader();
                        viewAllSellerAccounts();
                    }
                    else if (option == 2)
                    {
                        system("cls");
                        feedbackheader();
                        viewCustomerFeedback();
                    }
                    else if (option == 4)
                    {
                        system("cls");
                        reportheader();
                        salesreport();
                    }
                    else if (option == 6)
                    {
                        break;
                    }
                    else
                    {
                        cout << "----invalid option----" << endl;
                        hardeffect();
                    }
                }
            }
        }
        else if (option == 2)
        {
            while (true)
            {
                system("cls");
                customerheader();
                cout << "Enter product category or name to search:" << endl;
                cout << "1. Search Products" << endl;
                cout << "2. Purchase Product" << endl;
                cout << "3. Feedback Product" << endl;
                cout << "6. Main menu" << endl;
                cin >> option;
                if (option == 1)
                {
                    system("cls");
                    searchheader();
                    searchproducts();
                }
                else if (option == 2)
                {
                    system("cls");
                    purchaseproductheader();
                    purchaseproduct();
                }
                else if (option == 3)
                {
                    system("cls");
                    feedbackheader();
                    customerFeedback();
                }
                else if (option == 6)
                {
                    break;
                }
                else
                {
                    cout << "----Invalid option!----" << endl;
                    hardeffect();
                }
            }
        }
        else if (option == 3)
        {
            while (true)
            {
                system("cls");
                sellermenuheader();
                cout << "1. Create new account" << endl;
                cout << "2. Login" << endl;
                cout << "6. Back to main menu" << endl;
                cin >> option;

                if (option == 1)
                {
                    system("cls");
                    newaccountheader();
                    createaccount();
                }
                else if (option == 2)
                {
                    system("cls");
                    loginheader();
                    if (sellerlogin())
                    {
                        while (true)
                        {
                            system("cls");
                            sellermenuheader();
                            cout << "1. Add Product" << endl;
                            cout << "2. Update Product" << endl;
                            cout << "3. Delete Product" << endl;
                            cout << "4. View All Products" << endl;
                            cout << "5. Restock Products" << endl;
                            cout << "6.  Check is product low stock :" << endl;
                            cout << "9. Logout" << endl;
                            cin >> option;

                            if (option == 1)
                            {
                                system("cls");
                                addheader();
                                addproducts();
                            }
                            else if (option == 2)
                            {
                                system("cls");
                                updateheader();
                                updateproduct();
                            }
                            else if (option == 3)
                            {
                                system("cls");
                                deletheader();
                                if (delproduct())
                                {
                                    cout << "----Deleted successfuly----" << endl;
                                }
                                else
                                {
                                    cout << "----Record not found----" << endl;
                                    hardeffect();
                                }
                            }
                            else if (option == 4)
                            {
                                system("cls");
                                viewheader();
                                viewallproducts();
                            }
                            else if (option == 5)
                            {
                                system("cls");
                                restockheader();
                                restockProduct();
                            }
                            else if (option == 6)
                            {
                                system("cls");
                                lowStockheader();
                                lowStockalert();
                            }
                            else if (option == 9)
                            {
                                break;
                            }
                            else
                            {
                                cout << "----Invalid option!----" << endl;
                                hardeffect();
                            }
                        }
                    }
                }
                else if (option == 6)
                {
                    break;
                }
                else
                {
                    cout << "----Invalid option!----" << endl;
                    hardeffect();
                }
            }
        }
        else if (option == 9)
        {
            break;
        }
        else
        {
            cout << "----Invalid option!----" << endl;
            hardeffect();
        }
    }
    return 0;
}
void darazheader()
{
    cout << "_______________________________________________________________________________\n";
    cout << "_______________________________________________________________________________||\n";
    cout << "                                                                               ||\n";
    cout << "######          ########      #######           #######      ################  ||  " << endl;
    cout << "##    ##       ##      ##     ##     ##       ##      ##                 ###   ||  " << endl
         << "##     ##     ##        ##    ##      ##     ##        ##              ###     ||  " << endl
         << "##      ##    ##        ##    ##     ##      ##        ##            ###       ||  " << endl
         << "##      ##    ############    ##   ##        ############          ###         ||  " << endl
         << "##      ##    ##        ##    ##    ##       ##        ##        ###           ||  " << endl
         << "##     ##     ##        ##    ##     ##      ##        ##      ###             ||  " << endl
         << "##    ##      ##        ##    ##      ##     ##        ##    ###               ||  " << endl
         << "######        ##        ##    ##       ##    ##        ##   ###############    ||\n";
    cout << "                                                                               ||\n";
    cout << "______________________________________________________________________________ || \n";
    cout << "000000000000000000000000000000000000000000000000000000000000000000000000000000 ||\n";
    cout << "______________________________________________________________________________ ||\n";
}
void mainmenuheader()
{
    cout << "________________________" << endl
         << "@@@@@@@@@@@@@@@@@@@@@@@@" << endl
         << endl
         << "       MAIN MENU        " << endl
         << "________________________" << endl;
    cout << endl;
}
void loginheader()
{
    cout << "________________________" << endl
         << "@@@@@@@@@@@@@@@@@@@@@@@@" << endl
         << endl
         << "     LOGIN PASSWORD     " << endl
         << "________________________" << endl;
    cout << endl;
}
void adminheader()
{
    cout << "________________________" << endl
         << "@@@@@@@@@@@@@@@@@@@@@@@@" << endl
         << endl
         << "       ADMIN MENU       " << endl
         << "________________________" << endl;
    cout << endl;
}
void allsellerheader()
{
    cout << "________________________" << endl
         << "@@@@@@@@@@@@@@@@@@@@@@@@" << endl
         << endl
         << "      ALL SELLERS       " << endl
         << "________________________" << endl;
    cout << endl;
}
void feedbackheader()
{
    cout << "________________________" << endl
         << "@@@@@@@@@@@@@@@@@@@@@@@@" << endl
         << endl
         << "       FEED BACK       " << endl
         << "________________________" << endl;
    cout << endl;
}
void reportheader()
{
    cout << "________________________" << endl
         << "@@@@@@@@@@@@@@@@@@@@@@@@" << endl
         << endl
         << "      SALES REPORT       " << endl
         << "________________________" << endl;
    cout << endl;
}
void customerheader()
{
    cout << "________________________" << endl
         << "@@@@@@@@@@@@@@@@@@@@@@@@" << endl
         << endl
         << "        CUSTOMER        " << endl
         << "________________________" << endl;
    cout << endl;
}
void searchheader()
{
    cout << "________________________" << endl
         << "@@@@@@@@@@@@@@@@@@@@@@@@" << endl
         << endl
         << "     SEARCH RECOERD     " << endl
         << "________________________" << endl;
    cout << endl;
}
void purchaseproductheader()
{
    cout << "________________________" << endl
         << "@@@@@@@@@@@@@@@@@@@@@@@@" << endl
         << endl
         << "    PURCHASE PRODUCT    " << endl
         << "________________________" << endl;
    cout << endl;
}
void sellermenuheader()
{
    cout << "________________________" << endl
         << "@@@@@@@@@@@@@@@@@@@@@@@@" << endl
         << endl
         << "      SELLER MENU       " << endl
         << "________________________" << endl;
    cout << endl;
}
void newaccountheader()
{
    cout << "________________________" << endl
         << "@@@@@@@@@@@@@@@@@@@@@@@@" << endl
         << endl
         << "      NEW ACCOUNT       " << endl
         << "________________________" << endl;
    cout << endl;
}
void addheader()
{
    cout << "_______________________" << endl
         << "@@@@@@@@@@@@@@@@@@@@@@@" << endl
         << endl
         << "          ADD          " << endl
         << "_______________________" << endl;
    cout << endl;
}
void updateheader()
{
    cout << "________________________" << endl
         << "@@@@@@@@@@@@@@@@@@@@@@@@" << endl
         << endl
         << "         UPDATE          " << endl
         << "________________________" << endl;
    cout << endl;
}
void deletheader()
{
    cout << "________________________" << endl
         << "@@@@@@@@@@@@@@@@@@@@@@@@" << endl
         << endl
         << "         DELETE          " << endl
         << "________________________" << endl;
    cout << endl;
}
void viewheader()
{
    cout << "________________________" << endl
         << "@@@@@@@@@@@@@@@@@@@@@@@@" << endl
         << endl
         << "     VIEW PROFILES      " << endl
         << "________________________" << endl;
    cout << endl;
}
void restockheader()
{
    cout << "________________________" << endl
         << "@@@@@@@@@@@@@@@@@@@@@@@@" << endl
         << endl
         << "         RESTOCK        " << endl
         << "________________________" << endl;
    cout << endl;
}
void lowStockheader()
{
    cout << "________________________" << endl
         << "@@@@@@@@@@@@@@@@@@@@@@@@" << endl
         << endl
         << "        LOW STACK        " << endl
         << "________________________" << endl;
    cout << endl;
}