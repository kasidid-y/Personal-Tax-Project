#include <iostream>
#include <fstream>
#include<cctype>
#include<string>
#include <iomanip>
using namespace std;

//โปรแกรมคำนวณหาภาษีบุคคลธรรมดา สถานะโสด ของ Admin
// *ลดหย่อนภาษีสูงสุด 100,000 รายจ่ายคนปกติเฉลี่ย 100,000 ลดหย่อนภาษีคนปกติเฉลี่ย  60,000 ทั้งหมดต่อปี
class ReveneTaxDeprt{ //class สำหรับคำนวณภาษีและแสดงข้อมูลในไฟล์.txt ทั้งหมด
    public :
        
        double net_income; //รายได้สุทธิ
        double income , expense, deduction, tax; //รายได้,รายจ่าย,ลดหย่อน,ภาษี ต่อปี
        string name , id , current_id;
        
        void calTax(){ //คำนวณหาภาษี แบบขั้นบรรได  
            net_income = income - expense - deduction; //คำนวณหา รายได้สุทธิ = รายได้ทั้งหมด - รายจ่ายทั้งหมด - ลดหย่อน 
            if(net_income <= 150000){ //ไม่ต้องเสียภาษี
                tax = 0;
            }
            else if(net_income <= 300000){ //คำนวณหาภาษีที่ต้องจ่ายต่อปีตามลำดับ
                tax = (net_income - 150000) * 0.05 + 0;  //ภาษี = (รายได้สุทธิ - ช่วงต่ำสุดของขั้น(ขั้นนี้ ช่วง 150,000 ถึง 300,000))อัตราภาษี 10% + ภาษีสะสมสูงสุดของขั้น ตามลำดับ
            }
            else if(net_income <= 500000){
                tax = (net_income - 300000) * 0.1 + 7500; 
            }
            else if(net_income <= 750000){
                tax = (net_income - 500000) * 0.15 + 27500; 
            }
            else if(net_income <= 1000000){
                tax = (net_income - 750000) * 0.2 + 65000; 
            }
            else if(net_income <= 2000000){
                tax = (net_income - 1000000) * 0.25 + 115000;  
            }
            else if(net_income <= 5000000){
                tax = (net_income - 2000000) * 0.3 + 365000;  
            }
            else{
                tax = (net_income - 5000000) * 0.35 + 1265000; 
            }
            
        };
        
        void getRecord(){ //แสดงข้อมูลในไฟล์.txt ทั้งหมด
            ifstream file("Taxed.txt",ios::in); //เปิดไฟลเพื่ออ่านข้อมูล
            cout << endl;
            cout << "     ID" << "\t\tName" << "\t   Income\t" << "\t\t     Expense\t" << "\t\t     Deduction\t" << "\t Net income\t" << "\t Tax" <<endl;
            cout << " ---------------------------------------------------------------------------------------------------------------------------------------------------" <<endl;
                while (file >> id >> name >> income >> expense >> deduction >> net_income >> tax) { //วนลูปเอาข้อมูลเข้าตัวแปรที่กำหนด ทีละบรรทัด
                    cout << "   " <<  id;
                    cout << "\t" << name;
                    cout << "\t  " << fixed << setprecision(4) << income; //แสดงทศนิยม 4 ตำแหน่ง
                    cout << "\t\t\t    " << fixed << setprecision(4) << expense;
                    cout << "\t\t\t    " << fixed << setprecision(4) << deduction;
                    cout << "\t\t" << fixed << setprecision(4) << net_income;
                    cout << "\t\t" << fixed << setprecision(4) << tax <<endl;
                }
            cout << endl;
            file.close();
        };
        
};        
        
class FileManger :public ReveneTaxDeprt{  //class สำหรับค้นหาบิลภาษี, ลบบิลภาษีที่ไม่ต้องการ
    public :
        
        void writeFile(){  //ใส่ข้อมูลที่ได้รับลงไปในไฟล์
                ofstream file("Taxed.txt", ios::out | ios::app );  //เปิดไฟลเพื่อใส่ข้อมูลลงไป
                file << " " << id << " " << name << " " << income << " " << expense << " " << deduction << " " << net_income << " " << tax <<endl;
                file.close();
        };
            
        void getBill(string id){   //แสดงบิลภาษีที่ค้นหาจาก id
            bool found; 
            ifstream file("Taxed.txt",ios::in); 
            if(!file.is_open()){   //หาไฟล์ไม่เจอ
                cout << "*File cannot open!"; 
            }
            else{
                while (file >> current_id >> name >> income >> expense >> deduction >> net_income >> tax) { //วนลูปเอาข้อมูลเข้าตัวแปรที่กำหนด ทีละบรรทัด
                    if(id == current_id){ //ตรวจสอบว่า id เท่ากันหรือไม่
                        cout << "\n-----------------------------------" <<endl; //แสดงบิลภาษี
                        cout << "            Bill Tax             " <<endl;
                        cout << "-----------------------------------" <<endl;
                        cout << " ID         | " <<  id <<endl;
                        cout << " Name       | " << name <<endl;
                        cout << " Income     | " << fixed << setprecision(2) << income <<endl;
                        cout << " Expense    | " << fixed << setprecision(2) << expense <<endl;
                        cout << " Deduction  | " << fixed << setprecision(2) << deduction <<endl;
                        cout << "-----------------------------------" <<endl;
                        cout << " Net income | " << fixed << setprecision(2) << net_income <<endl;
                        cout << "-----------------------------------" <<endl;
                        cout << " Tax        | " << fixed << setprecision(2) << tax <<endl;
                        cout << "-----------------------------------\n" <<endl;
                        found = true;
                        break;
                    }
                }
                if(!found){    //หา id ไม่เจอ
                    cout << "*Record not found."<<endl;
                }
                file.close();
            }
        };    
        
        void deleteBill(string id){ //ลบบิลภาษีที่ไม่ต้องการในไฟล์.txt (โดยหาจาก id ที่ต้องการลบ มีการสร้างไฟล์ใหม่แล้วนำข้อมูลที่ไม่ต้องการลบใส่เข้าไป แล้วลบไฟล์เก่าทิ้ง เปลี่ยนชื่อไฟล์ให้เป็นเหมือนเดิม)
            bool found;
            ifstream file("Taxed.txt",ios::in);  
            ofstream newFile("newFile.txt", ios::out);  //สร้างไฟล์ใหม่ขึ้นมา
            if(!file.is_open()){
                cout << "*File cannot open!";
            }
            else{
                while (file >> current_id >> name >> income >> expense >> deduction >> net_income >> tax) {
                    if(id == current_id){ //ตรวจสอบว่า id เท่ากันหรือไม่
                        cout << "*Record deleted successfully. " << endl;
                        found = true;
                        continue; //ข้าม if อันนี้ไป เพื่อเพิ่มข้อมูลที่ไม่ต้องการลบลงไฟล์ใหม่
                    }
                    newFile << current_id << " " << name << " " << income << " " << expense << " " << deduction << " " << net_income << " " << tax << endl; //ใส่ข้อมูลลงไฟล์ใหม่
                }
        
                file.close();
                newFile.close();
                remove("Taxed.txt"); //ลบไฟล์เดิม
                rename("newFile.txt", "Taxed.txt"); //เปลี่ยนชื่อไฟล์ใหม่เป็นชื่อไฟล์เดิม
                if(!found){
                    cout << "*Record not found." << endl; 
                }
            }
        };
};

class Admin :public FileManger{   //class สำหรับรับข้อมูล,เช็ค password
    private :  
        string username;
        string password = "12345";  //ใช้ login สำหรับ admin
        bool checkPW; 
        
    public :
        int checkID(string id); //
        
        void inputInfo(){  //ใช้รับข้อมูล รายได้, รายจ่าย, ลดหย่อน, id, ชื่อ
            while(true){
                cout << " Enter tax payer id(5 digits): "<<endl; cin>> id;
                if(checkID(id) == 0){   //ใส่ id ถูกต้องตามที่กำหนด
                    cout << "*ID is Valid."<<endl;
                    break;
                }
                else {  //ใส่ id ไม่ถูกต้องตามที่กำหนด
                    cout << "*ID is invalid."<<endl;
                }
            }
            cout << " Enter tax payer name: "<<endl; cin>> name;
            cout << " Enter yearly income: "<<endl; cin>> income;
            if (cin.fail()) { //ตรวจสอบข้อมูลที่ใส่ไปตรงกับชนิดของตัวแปรหรือไม่ ในที่นี้คือ double
                cout << "*Invalid input." << endl; //ถ้าไม่แสดงบอกไม่ถูกต้อง และออกจากโปรแกรม
                exit(0);
            }
            cout << " Enter yearly expense: "<<endl; cin>> expense;
            if (cin.fail()) {
                cout << "*Invalid input." << endl;
                exit(0);
            }
            cout << " Enter deduction: "<<endl; cin>> deduction;
            if (cin.fail()) {
                cout << "*Invalid input." << endl;
                exit(0);
            }
        };
        
        Admin() {  //แสดงเมื่อเริ่มโปรแกรม
            cout << "*Login as admin."<<endl; 
        }
        
        Admin(string password1) {  //ใช้เช็ค password ที่รับมาจาก main กับ password ที่กำหนดไว้
            if (password1 == password) { 
                checkPW = true;
            }
            else {
                checkPW = false;
            }
        }
        
        Admin(string username, string password); //ประกาศไว้ใช้งานกับ constructor ที่จะแสดงเมื่อ login สำเร็จ
        
        Admin(int count){
            if(count == 5){
                cout << "*Enter Invalid password exceed 5 times!"<<endl;
                exit(0);
            }
                
        }
        
        bool Login(){  //ใช้ return ค่า checkPW ที่ไว้เก็บค่า true,false หลังจากเช็ค paassword เสร็จ
            return checkPW;
        }
};
Admin::Admin(string username, string password){  //เป็น constructor ของคลาส Admin โดยจะแสดงเมื่อ login สำเร็จ
    cout<< "*Admin "<< username << " has logged in."<<endl;
}

int Admin::checkID(string id){  //ตรวจสอบความถูกต้องของ id ใชัจำกัดจำนวนชื่อ id , ห้ามเริ่มต้นด้วย 0, ห้ามยาวกว่าหรือน้อยกว่า 5 ตัว,
    int i = 0;
    string record;
    if(id.empty()){ //เป็นตัวแปรเปล่าๆหรือไม่ *ไม่มีค่า
        cout << "*Please create some ID"<<endl; 
            return 1;
    }
    if(id[0] == '0'){ //id , ห้ามเริ่มต้นด้วย 0
        cout<< "*ID must not start with 0"<<endl;
        return 1;
    }  
    if(id.length() > 5 or id.length() < 5 ){ //ตรวจสอบว่ายาวกว่าหรือน้อยกว่า 5 ตัว
        cout<< "*ID must have 5 digits."<<endl;
        return 1;
    }
     //ตรวจสอบว่ามีแค่ตัวเลขอย่างเดียวใช่หรือไม่
    for(i; i<id.length();i++){
       if( !isdigit(id[i])){
            cout<< "*ID must be all numeric."<<endl;
            return 1;
            break;
        }
    }
    ifstream file("Taxed.txt",ios::in);  //ใช้ตรวจสอบว่า id นี้ มีอยู่ในไฟล์หรือไม่
        if(!file.is_open()){
            cout << "*File cannot open!";
        }
        while (file>>current_id) {
            if(current_id == id){ // ตรวจสอบว่า id เท่ากันหรือไม่
                cout << "*ID has already been used." <<endl;
                return 1;
                file.close();
            }
        }
        return 0;
};


int main()
{
    string num,id,username,password;
    bool login = false;
    int count = 0;
    Admin admin1;  //ประกาศ admin1 และจะเรียก constructor ของคลาส Admin ที่ไม่มีพารามิเตอร์มาแสดง 
    while(true){
        cout << "\n --------[ HOME ]-------- " <<endl;  //หน้าแรก
        cout << " 1. Login \t 2. Exit" <<endl;
        cout << "Choose: "; cin>> num;
        if(num == "1"){  //เลือก login
            cout << "\n [ LOGIN ] " << endl; //หน้า 2
            do {
                cout << " Enter username: "; 
                cin >> username;
                cout << " Enter password: ";
                cin >> password;
                
                Admin admin2(password);  
                login = admin2.Login();   //เอาค่าจากฟังก์ชัน Login( ) ใส่เข้าไปในตัวแปร login
                
                if (!login) {   //จะแสดง ถ้า login เป็น false
                    cout << "*Invalid password. Please try again." << endl;
                    count++;
                    Admin admin2(count);
                }
                else{ //จะแสดง ถ้า login เป็น true
                    Admin admin3(username,password);  //เอาไว้เรียกใช้ constructor เมื่อ login สำเร็จ
                }
            } while (!login); //จะออกจากลูปเมื่อ ค่า login เป็น true 
            
            while(true){
                cout << " \n [  ADMIN  ]" <<endl; //หน้า 3 //มีแสดงข้อมูลทั้งหมดในไฟล์, เพิ่มข้อมูลลงไฟล์, ลบข้อมูลที่ไม่ต้องการในไฟล์, ค้นหาบิลภาษี, กลับไปหน้าแรก
                cout << "  1. View All Record   2. Add a record   3. Remove a record   4. Get bill   5. Back to Home" <<endl;
                cout << "Choose: "; cin>>num;  
                if(num == "1"){ //มีแสดงข้อมูลทั้งหมดในไฟล์
                    admin1.getRecord();
                }
                else if(num == "2"){ //เพิ่มข้อมูลลงไฟล์
                    cout << " \n [  ADD RECORD  ]" <<endl;
                    admin1.inputInfo();
                    admin1.calTax();
                    admin1.writeFile();
                    cout << "*Complete!" <<endl;
                }
                else if(num == "3"){ //ลบข้อมูลที่ไม่ต้องการในไฟล์
                    cout << " \n [  REMOVE A RECORD  ]" <<endl;
                    cout<< " Enter an ID wanted to delete: "; cin>>id; //ใส่ id เพื่อค้นหา id ในไฟล์
                    admin1.deleteBill(id);
                }
                else if(num == "4"){  //ลบข้อมูลที่ไม่ต้องการในไฟล์
                    cout << " \n [  GET BILL  ]" <<endl;
                    cout<< " Enter an ID wanted to print out bill: "; cin>>id;   //ใส่ id เพื่อค้นหา id ในไฟล์
                    admin1.getBill(id);
                }
                else if(num == "5"){   //ค้นหาบิลภาษี
                    break;
                }
                else{
                    cout << "*There has only 2 options!"<<endl;
                    cout << "*You only enter either 1 or 2."<<endl;
                    cout << "*Please enter number again."<<endl;
                }
            }
        }
        else if(num == "2"){  //ออกจากโปรแกรม
            cout << "\n  Bye bye  " <<endl;
            exit(0);
        }
        else {
            cout << "*There has only 2 options!"<<endl;
            cout << "*You only enter either 1 or 2."<<endl;
            cout << "*Please enter number again."<<endl;
        }
    }
    return 0;
}


