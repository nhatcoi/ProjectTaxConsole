#include<iostream>
#include<iomanip>

using namespace std;

double
TAX_DEDUCTION = 11.0, // giam tru thue
DEP_FEE = 4.4, // giam tru phi phu thuoc
TAX_LIMIT[7] = {0, 0.25, 0.75, 1.65, 3.25, 5.85, 9.85}, // Ham muc thue.
TAX_RATE[7] = {0, 5, 10, 18, 32, 52, 80};   // ham muc tang % thue.

double taxSal[12], sal[12]; // Thue thu nhap theo thang, và luong theo thang.

string name; // ten nguoi dung.
int year = 0, numDep = 0; // nam tinh thue, so nguoi phu thuoc.

double taxableIncome = 0, sumTaxableIncome = 0, taxMonth = 0; // Thu nhap tinh thue, tong thu nhap tinh thue, thue thang.

// main menu
void menu() {
    cout << "--------------------------------------" << endl;
    cout << "|           MENU CHƯƠNG TRÌNH          |" << endl;
    cout << "--------------------------------------" << endl;
    cout << "|  1. Han muc mien tru thue            |" << endl;
    cout << "|  2. Nhap thong tin tinh thue         |" << endl;
    cout << "|  3. Tinh thue TNCN theo thang        |" << endl;
    cout << "|  4. Quyet toan thue TNCN ca nam      |" << endl;
    cout << "|  0. Thoat chuong trinh               |" << endl;
    cout << "--------------------------------------" << endl;
    cout << "Moi ban nhap: ";
}

// Hàm generics check nhap gia tri > 0
template <typename T>
T check(T x) {
    cin >> x;
    bool check = true;
    while (check) {
        if (x < 0) {
            cout << "Da nhap sai gia tri, vui long nhap lai :";
            cin >> x;
            check = true;
        } else {
            check = false;
        }
    }
    return x;
}

// 1. Han muc
void taxLimit() {
    int choice;
    do {
        cout << "Mien tru gia canh ban than la " << TAX_DEDUCTION << " trieu VND" << endl;
        cout << "Mien tru nguoi phu thuoc la " << DEP_FEE << " trieu VND / nguoi" << endl;
        cout << "Ban co muon thay doi muc giam tru thue khong?" << endl;
        cout << "1. Thay doi\n" << "0.Quay lai" << endl;
        cout << "Nhap : ";
        cin >> choice;
        while (choice != 1 && choice != 0) {
            cout << "Sai gia tri, nhap lai: ";
            cin >> choice;
        }

        if(choice == 1) {
            double m = TAX_DEDUCTION, n = DEP_FEE;
            cout << "Nhap mien tru gia canh moi (trieu VND) : "; TAX_DEDUCTION = check(TAX_DEDUCTION);
            cout << "Mien tru nguoi phu thuoc la (trieu VND): "; DEP_FEE = check(DEP_FEE);
            cout << "Du lieu quan trong, ban da chac chan thay doi muc phi chu?" << endl;
            cout << "1. OK\n" << "0. Quay lai";
            int k = 0; k = check(k);
            while(k>1) {
                cout << "Sai gia tri, nhap lai: "; k = check(k);
            }
            if(k==0) {
                TAX_DEDUCTION = m;
                DEP_FEE = n;
                break;
            }
            cout << "\nMuc mien tru da duoc cap nhat!!" << endl;
        }
    } while (choice != 0);
}

// 2. Hàm nhập thông tin
void displayInfo() {
    cout << "---------------------- THONG TIN -------------------" << endl;
    cout << left << setw(20) << "| Ten:               " << setw(30) << right << name << "|" << endl;
    cout << left << setw(20) << "| Nam tinh thue:     " << setw(30) << right << year << "|" << endl;
    cout << left << setw(20) << "| So nguoi phu thuoc:" << setw(30) << right << numDep << "|" << endl;
    cout << "----------------------------------------------------" << endl;
}

void enterInfo() {

    cout << "Nhap ten : ";
    cin.ignore();
    getline(cin, name);

    cout << "Nam tinh thue : ";
    year = check(year);
    cout << "So nguoi phu thuoc : ";
    numDep = check(numDep);

    displayInfo();
}

// 3. Tinh thue TNCN theo thang.
// Ham cong thuc tinh thue theo thang
void recipe(int i) {
    taxableIncome = sal[i] - (numDep * DEP_FEE) - TAX_DEDUCTION;

    if (taxableIncome <= 0) {
        taxMonth = 0;
    } else {
        int n = sizeof(TAX_RATE) / sizeof(TAX_RATE[0]);
        for (int j = 0; j < n; ++j) {
            if (taxableIncome < TAX_RATE[j + 1]) {
                // rate tinh thue   // muc tru thue
                taxMonth = taxableIncome * (0.05 + 0.05 * j) - TAX_LIMIT[j];
                break;
            }
            if(taxableIncome > TAX_RATE[n-1]) {
                taxMonth = taxableIncome * (0.05 + 0.05 * 6) - TAX_LIMIT[6];
            }
        }
    }
    sumTaxableIncome += taxableIncome;
    taxSal[i] = taxMonth;
}

// Ham tinh thue TNCN theo cac thang.
double * calIncomeTaxForMonths() {
    if(name.empty()) {
        cout << "Vui long thuc hien nhap thong tin o muc 2 truoc khi tinh thue!" << endl;
        return nullptr;
    }

    int a = 0;
    do {
        cout << "1. Tinh thue voi mot thang trong nam." << endl;
        cout << "2. Tinh thue voi ca 12 thang trong nam." << endl;
        cout << "3. Hien thi cac thang da nop thue. " << endl;
        cout << "0. Quay lai menu." << endl;

        int cnt = 0;
        cin >> a;
        while(a > 4 || a < 0) {
            cout << "Sai gia tri, nhap lai :"; cin >> a;
        }


        switch (a) {
            case 1:{
                int month = 1;
                cout << "Nhap thang : ";
                cin >> month;

                while (month <=0 || month > 12) {
                    cout << "Sai gia tri, vui long nhap lai : ";
                    cin >> month;
                }

                cout << "Nhap luong thang " << month << " la : ";
                double salaryMonth = 0;
                sal[month-1] = check(salaryMonth);

                recipe(month-1);
                // Output ra thuế 12 tháng
                for(int index = 0; index < 12; index++) {
                    if(taxSal[index] != 0) {
                        cout << "Thue thang " << index + 1 << " la : " << taxSal[index] << endl;
                    }
                }
                break;
            }

            case 2:{

                for(int i = 0; i < 12; i++) {
                    cout << "Luong thang " << i + 1 << " la : ";
                    sal[i] = check(sal[i]);
                } cout << endl;

                for(int i = 0; i < 12; i++) {
                    recipe(i);
                }

                // Output ra thuế 12 tháng
                for(int index = 0; index < 12; index++) {
                    if(taxSal[index] != 0) {
                        cout << "Thue thang " << index + 1 << " la : " << taxSal[index] << endl;
                    }
                } cout << endl;
                break;
            }

            case 3: {
                // Output ra thuế 12 tháng
                for(int i = 0; i < 12; i++) {

                    if(taxSal[i] != 0) {
                        cout << fixed << setprecision(3);
                        cout << "Thue thang " << i + 1 << " la: " << taxSal[i] << endl;
                        cnt++;
                    }
                } cout << endl;
                if(cnt == 0) {
                    cout << "Khong co du lieu thue, do chua nhap thu nhap ca nhan." << endl;
                }
                break;
            }
        }
    } while (a!=0);

    return taxSal;
}

// 4. Quyet toan ca nam
// Ham tinh tong thue TNCN da dong trong nam.
double sumTaxIncome() {
    double sum = 0;
    for (double salary : taxSal) {
        sum += salary;
    }
    return sum;
}

// Ham tinh tong TNCN trong ca nam
double sumIncome() {
    double sum = 0;
    for (double i : sal) {
        sum += i;
    }
    return sum;
}

// Ham quyet toan thue TNCN ca nam.
double calculateTax(double income, double rate) {
    return income * rate;
}

void taxForYear() {
    double taxThresholds[] = {60, 120, 216, 384, 624, 960}; // Nguong muc chiu thue
    double rates[] = {0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35}; // ti le theo nguong

    double temp = 0; // thue phai dong

    for (int i = 0; i < sizeof(taxThresholds) / sizeof(taxThresholds[0]); ++i) {
        if (sumTaxableIncome <= taxThresholds[i]) {
            temp += calculateTax(sumTaxableIncome - (i > 0 ? taxThresholds[i - 1] : 0), rates[i]);
            break;
        } else {
            temp += calculateTax(taxThresholds[i] - (i > 0 ? taxThresholds[i - 1] : 0), rates[i]);
        }
    }

    displayInfo(); // hien thi thong tin
    cout << "Tong thu nhap ca nam : " << sumIncome() << endl;
    cout << "Tong thue TNCN da dong : " << sumTaxIncome() << endl;
    cout << "Tong thue phai dong : " << temp << endl;

    if (temp < sumTaxIncome()) {
        cout << "Truy linh: " << sumTaxIncome() - temp << endl;
    } else if (temp == sumTaxIncome()) {
        cout << "Khong phai truy thu, truy linh." << endl;
    } else {
        cout << "Truy thu: " << temp - sumTaxIncome() << endl;
    }
}


int main() {
    int feature = 0;
    do {
        menu();
        feature = check(feature);
        if(feature > 4 ) {
            cout << "Khong co tinh nang nay, vui long xem va nhap lai!!!" << endl;
            continue;
        }
        switch (feature) {
            case 1: {
                // Thông tin về mức thuế
                taxLimit();
                break;
            }
            case 2: {
                // Nhập thông tin
                enterInfo();
                break;
            }
            case 3: {
                // Mảng chứa thuế của 12 tháng
                calIncomeTaxForMonths();

                break;
            }
            case  4: {
                // Thuế cả năm
                taxForYear();
            }
            default: {
                cout << "\nThuc hien xong " << endl;
            }
        }

    } while (feature!=0);
    return 0;
}
// end