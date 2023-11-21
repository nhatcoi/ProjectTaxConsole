#include<iostream>
#include<iomanip>

using namespace std;

struct taxLimits {
    float
            taxDeduction = 11.0, // giam tru
    depFee = 4.4; // giam tru phi phu thuoc
    const float
            TAX_LIMIT[7] = {0, 0.25, 0.75, 1.65, 3.25, 5.85, 9.85}, // Ham muc thue.
    TAX_RATE[7] = {0, 5, 10, 18, 32, 52, 80},   // ham muc tang % thue.
    TAX_THRESHOLDS[6] = {60, 120, 216, 384, 624, 960}, // Nguong muc chiu thue
    RATES[7] = {0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35}; // ti le theo nguong
} limit;

struct UserInfo{
    string name; // ten nguoi dung.
    int year = 0, numDep = 0; // nam tinh thue, so nguoi phu thuoc.
} inFor;

struct taxInfo {
    float taxSal[12]{}, sal[12]{}, // Thue thu nhap theo thang, và luong theo thang.
    taxableIncome = 0, sumTaxableIncome = 0, taxMonth = 0; // Thu nhap tinh thue, tong thu nhap tinh thue, thue thang.
} tax;

void menu();
template <typename T>
T check(T x);
void taxLimit();
void enterInfo();
float * calIncomeTaxForMonths();
void taxForYear();

int main() {
    short feature = 0;
    do {
        menu();
        feature = check(feature); cout << endl;
        if(feature > 4) {
            cout << "Khong co tinh nang nay, vui long xem va nhap lai!!!" << endl;
            continue;
        }
        switch (feature) {
            case 1: {
                // Thong tin ve muc thue
                taxLimit();
                break;
            }
            case 2: {
                // Nhap thong tin
                enterInfo();
                break;
            }
            case 3: {
                // Thue cua cac thang
                calIncomeTaxForMonths();
                break;
            }
            case  4: {
                // Thue ca nam
                taxForYear();
                break;
            }
            default: {
                cout << "\nThuc hien xong " << endl;
            }
        }
    } while (feature!=0);
    return 0;
}
// end

//void clearConsole() {
//    system("clear");
//}

// main menu
void menu() {
    cout << "----------------------------------------\n"
            "|           MENU CHUONG TRINH          |\n"
            "----------------------------------------\n"
            "|  1. Han muc mien tru thue            |\n"
            "|  2. Nhap thong tin tinh thue         |\n"
            "|  3. Tinh thue TNCN theo thang        |\n"
            "|  4. Quyet toan thue TNCN ca nam      |\n"
            "|  0. Thoat chuong trinh               |\n"
            "----------------------------------------\n"
            "Moi ban nhap: ";
}

// Hàm generics check nhap gia tri > 0
template <typename T>
T check(T x) {
    cin >> x;
    bool check = true;
    while (check) {
        check = (x < 0) && (cout << "Da nhap sai gia tri, vui long nhap lai :", cin >> x, true);
    }
    return x;
}

// 1. Han muc
void taxLimit() {
    int choice;
    do {
        cout << "Mien tru gia canh ban than la " << limit.taxDeduction << " trieu VND" << endl;
        cout << "Mien tru nguoi phu thuoc la " << limit.depFee << " trieu VND / nguoi" << endl;
        cout << "Ban co muon thay doi muc giam tru thue khong?" << endl;
        cout << "1. Thay doi\n" << "0.Quay lai" << endl;
        cout << "Nhap : ";
        cin >> choice;
        while (choice != 1 && choice != 0) {
            cout << "Sai gia tri, nhap lai: ";
            cin >> choice;
        }

        if(choice == 1) {
            // m,n la 2 bien temporary de luu tru han muc tru va phi phu thuoc.
            float m = limit.taxDeduction, n = limit.depFee;
            // Thay doi muc mien tru thue.
            cout << "Nhap mien tru gia canh moi (trieu VND) : "; limit.taxDeduction = check(limit.taxDeduction);
            cout << "Mien tru nguoi phu thuoc la (trieu VND): "; limit.depFee = check(limit.depFee);
            cout << "Du lieu quan trong, ban da chac chan thay doi muc phi chu?" << endl;
            cout << "1. OK\n" << "0. Quay lai" << endl;

            // check validation
            int k; cin >> k;
            while(k!=0 && k!=1) {
                cout << "Sai gia tri, nhap lai: "; cin >> k;
            }

            // Khong thay doi
            if(k==0) {
                limit.taxDeduction = m;
                limit.depFee = n;
                break;
            }
            cout << "\nMuc mien tru da duoc cap nhat!!" << endl;
        }
    } while (choice != 0);
}

// 2. Ham thong tin
void displayInfo() { // display thong tin
    cout << "\n---------------------- THONG TIN -------------------" << endl;
    cout << left << setw(20) << "| Ten:               " << setw(30) << right << inFor.name << "|" << endl;
    cout << left << setw(20) << "| Nam tinh thue:     " << setw(30) << right << inFor.year << "|" << endl;
    cout << left << setw(20) << "| So nguoi phu thuoc:" << setw(30) << right << inFor.numDep << "|" << endl;
    cout << "--------------------------END-----------------------\n" << endl;
}

void enterInfo() {  // input thong tin

    cout << "Nhap ten : ";
    cin.ignore();
    getline(cin, inFor.name);

    cout << "Nam tinh thue : ";
    inFor.year = check(inFor.year);
    while(inFor.year < 2000) {
        cout << "Tinh thue ap dung voi nien dai 2000 tro di.\nNam tinh thue: "; inFor.year = check(inFor.year);
    }
    cout << "So nguoi phu thuoc : ";
    inFor.numDep = check(inFor.numDep);

    displayInfo();

    cout << "0. Thoat." << endl; int out; cin >> out;
    while(out!=0) { cout << "Sai du lieu, nhap lai : "; cin >> out; }

}

// 3. Tinh thue TNCN theo thang.
// Ham cong thuc tinh thue theo thang
void recipe(int i) {
    // Thu nhap tinh thue = Muc luong thang - snpt * muc phu thuoc - muc mien tru thue.
    tax.taxableIncome = tax.sal[i] - (static_cast<float>(inFor.numDep) * limit.depFee) - limit.taxDeduction;

    if (tax.taxableIncome <= 0) {
        tax.taxMonth = 0; // Khong phai dong thue.
    } else {
        // so size cua muc thue (7)
        int n = sizeof(limit.TAX_RATE) / sizeof(limit.TAX_RATE[0]);
        for (int j = 0; j < n; ++j) {
            if (tax.taxableIncome < limit.TAX_RATE[j + 1]) {
                // thu nhap tinh thue < muc tru thue thu j + 1
                tax.taxMonth = static_cast<float>(tax.taxableIncome * (0.05 + 0.05 * j) - limit.TAX_LIMIT[j]);
                break;
            }
            if(tax.taxableIncome > limit.TAX_RATE[n-1]) {
                tax.taxMonth = static_cast<float>(tax.taxableIncome * (0.05 + 0.05 * (n-1)) - limit.TAX_LIMIT[6]);
            }
        }
    }
    tax.sumTaxableIncome += tax.taxableIncome; // Tong thu nhap tinh thue
    tax.taxSal[i] = tax.taxMonth; // Tong luong 12 thang
}

// Ham tinh thue TNCN theo cac thang.
float * calIncomeTaxForMonths() {
    // check validation thong tin nguoi dung
    if(inFor.name.empty()) {
        cout << "Vui long thuc hien nhap thong tin o muc 2 truoc khi tinh thue!" << endl;
        return nullptr;
    }

    short a = 0;
    do {
        // tinh thue va xem thue
        cout << "1. Tinh thue voi mot thang trong nam." << endl;
        cout << "2. Tinh thue voi ca 12 thang trong nam." << endl;
        cout << "3. Hien thi cac thang da nop thue. " << endl;
        cout << "0. Quay lai menu." << endl;

        short cnt = 0;
        cin >> a;
        while(a > 4 || a < 0) {
            cout << "Sai gia tri, nhap lai :"; cin >> a;
        }
        switch (a) {
            case 1:{
                int month = 1;
                cout << "Nhap thang : ";
                cin >> month;
                //check validation
                while (month <=0 || month > 12) {
                    cout << "Sai gia tri, vui long nhap lai : ";
                    cin >> month;
                }

                // Luong thang
                cout << "Nhap luong thang " << month << " la (trieu VND): ";
                float salaryMonth = 0;
                tax.sal[month-1] = check(salaryMonth);

                // Cong thuc tinh thue theo thang
                recipe(month-1);

                // Output ra thue thang
                cout << fixed << setprecision(6);
                cout << "Thue thang " << month << " la : " << tax.taxSal[month-1] << " (trieu VND)"<< endl << endl;
                break;
            }

            case 2:{
                // Input 12 thang luong
                for(int i = 0; i < 12; i++) {
                    cout << "Luong thang " << i + 1 << " la (trieu VND): ";
                    tax.sal[i] = check(tax.sal[i]);
                } cout << endl;

                // Tinh thue theo cong thuc voi 12 thang
                for(int i = 0; i < 12; i++) {
                    recipe(i);
                }

                // Output ra thuế 12 tháng
                for(int index = 0; index < 12; index++) {
                    if(tax.taxSal[index] != 0) {
                        cout << fixed << setprecision(6);
                        cout << "Thue thang " << index + 1 << " la : " << tax.taxSal[index] << " (trieu VND)"<< endl;
                    }
                } cout << endl;
                break;
            }

            case 3: {
                // Output ra thuế 12 tháng
                cout << setw(10) << left << "Thang";
                cout << setw(35) << left << "| Thue (trieu VND)" << endl;
                cout << "------------------------------"<< endl;

                for(int i = 0; i < 12; i++) {
                    if(tax.taxSal[i] != 0) {
                        cout << setw(10) << left << "Thang " + to_string(i + 1);
                        cout << setw(25) << left << "| " + to_string(tax.taxSal[i]) << endl;
                        cnt++;
                    }
                }
                cout << "------------------------------"<< endl;
                if(cnt == 0) cout << "Khong co du lieu phai nop thue, hoac do chua nhap thu nhap ca nhan.\n" << endl;
                break;
            }
            default: cout << "Xong\n" << endl;
        }
    } while (a!=0);
    return tax.taxSal;
}

// 4. Quyet toan ca nam
// Ham tinh tong thue TNCN da dong trong nam.
float sumTaxIncome() {
    float sum = 0;
    for (float salary : tax.taxSal) {
        sum += salary;
    }
    return sum;
}

// Ham tinh tong TNCN trong ca nam
float sumIncome() {
    float sum = 0;
    for (float i : tax.sal) {
        sum += i;
    }
    return sum;
}

// Ham quyet toan thue TNCN ca nam.
float calculateTax(float income, float rate) {
    return income * rate;
}

void taxForYear() {
    //thue da dong ca nam
    float taxPaid = sumTaxIncome();
    // thue phai dong ca nam
    float taxPay = 0;

    // Tinh thue phai dong ca nam
    int n = sizeof(limit.TAX_THRESHOLDS) / sizeof(limit.TAX_THRESHOLDS[0]); // size cua han muc (6)
    for (int i = 0; i < n; ++i) {
        if (tax.sumTaxableIncome <= limit.TAX_THRESHOLDS[i]) {
            taxPay += calculateTax(tax.sumTaxableIncome - (i > 0 ? limit.TAX_THRESHOLDS[i - 1] : 0), limit.RATES[i]);
            break;
        } else {
            taxPay += calculateTax(limit.TAX_THRESHOLDS[i] - (i > 0 ? limit.TAX_THRESHOLDS[i - 1] : 0), limit.RATES[i]);
        }
    }

    // truy linh, truy thu
    float retrieval = taxPaid - taxPay;

    // hien thi thong tin
    cout << "\n---------------------- THONG TIN -------------------" << endl;
    cout << left << setw(20) << "| Ten:               " << setw(30) << right << inFor.name << " |" << endl;
    cout << left << setw(20) << "| Nam tinh thue:     " << setw(30) << right << inFor.year << " |" << endl;
    cout << left << setw(20) << "| So nguoi phu thuoc:" << setw(30) << right << inFor.numDep << " |" << endl;
    cout << "|---------------------------------------------------|" << endl;
    cout << "| Tong thu nhap ca nam : " << setw(14) << right << sumIncome() << " (trieu VND) |" << endl;
    cout << "| Tong thue TNCN da dong : " << setw(12) << right << sumTaxIncome() << " (trieu VND) |" << endl;
    cout << "| Tong thue phai dong : " << setw(15) << right << taxPay << " (trieu VND) |" << endl;
    cout << "|---------------------------------------------------|" << endl;

    // Quyet toan truy linh, truy thu.
    if (taxPay < sumTaxIncome()) {
        cout << "Truy linh: " << setw(28) << right << retrieval << " (trieu VND) |" << endl;
    } else if (taxPay == sumTaxIncome()) {
        cout << "Khong phai truy thu, truy linh." << endl;
    } else {
        retrieval *= (-1);
        cout << "Truy thu: " << setw(29) << right << retrieval << " (trieu VND) |" << endl;
    }
    cout << "--------------------------END-----------------------\n" << endl;

    // out
    cout << "0. Thoat." << endl; short out; cin >> out;
    while(out != 0) { cout << "Nhap sai du lieu, nhap lai : "; cin >> out; }
}


/* -- END PROJECT --
 * github : https://github.com/nhatcoi/ProjectTaxConsole
*/