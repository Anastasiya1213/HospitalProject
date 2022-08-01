#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <iomanip>
#include <windows.h>
#include <time.h>
#include <ctime>

using namespace std;

static int count_patient;
static int count_medics;
static int count_keepRoom;
static int sub_menu = 1;
static int check_number;

void correctInput(string &text)
{
	error_number:
    if(check_number == 1) { cout << "Full name must not contain a number! Try again:"; check_number = 0; }
	while(!(getline(cin, text, '\n')) || text.length() < 5 || text[0] == ' ') {
		cin.clear();
        fflush(stdin);
        cout << "Full name must not start with a space or be less than 5 characters! Try again: ";
	}
	for(int i(0); i < text.length(); i++) {
        if(text[i] == '1' || text[i] == '2' || text[i] == '3' || text[i] == '4' || text[i] == '5' || text[i] == '6' || text[i] == '7' || text[i] == '8' || text[i] == '9' || text[i] == '0') {
            check_number = 1;
            goto error_number;
        }
    }
}

int correctNumberInput(int &varCheck, int minVar, int maxVar)
{
    while (!(cin >> varCheck) || (cin.peek() != '\n') || varCheck < minVar || varCheck > maxVar) {
        cout << "You have entered an invalid value! Try again: ";
        cin.clear();
        fflush(stdin);
    }
}

class Patients {
	protected:
		string fullname[10], text_bresult, rome_bgroup;
		int age[10], bgroup[10], bresult[10], empty_patient;
	public:
		Patients() {
			fullname[0] = "Patient #1";
			age[0] = 45;
			bgroup[0] = 1;
			bresult[0] = 0;

			fullname[1] = "Patient #2";
			age[1] = 19;
			bgroup[1] = 2;
			bresult[1] = 1;

			fullname[2] = "Patient #3";
			age[2] = 22;
			bgroup[2] = 4;
			bresult[2] = 0;

			count_patient = 3;
		}

		string GetFullName(int index) { return fullname[index]; }
		string GetRomeBGroup()	      { return rome_bgroup;     }
		string GetTextBResult()       { return text_bresult;	}
		int    GetAge(int index)      { return age[index];	    }
		int    GetBGroup(int index)   { return bgroup[index];	}
		int    GetBResult(int index)  {	return bresult[index];	}
		int    GetEmpty()             {	return empty_patient;	}

		Patients & SetFullName(int index, string text) { fullname[index] = text;   }
		Patients & SetAge(int index, int numbers) 	   { age[index] = numbers;     }
		Patients & SetBGroup(int index, int numbers)   { bgroup[index] = numbers;  }
		Patients & SetBResult(int index, int numbers)  { bresult[index] = numbers; }

		void RomeBGroup(int bgroup, int bresult) {
			if(bgroup == 1)  rome_bgroup = "I";
			if(bgroup == 2)  rome_bgroup = "II";
			if(bgroup == 3)  rome_bgroup = "III";
			if(bgroup == 4)  rome_bgroup = "IV";
			if(bresult == 0) text_bresult = "Negative";
			if(bresult == 1) text_bresult = "Positive";
		}

		void PrintPatients() {
			if(count_patient == 0) {
				cout << "There are no patients!" << endl;
				empty_patient = 1;
			} else {
				empty_patient = 0;
				for(int i = 0; i < count_patient; i++) {
					cout << i+1 << ". " << GetFullName(i) << endl;
				}
			}
		}

		void PrintInfoPatients() {
			if(count_patient == 0) {
				cout << "There are no patients!" << endl;
				empty_patient = 1;
			} else {
				empty_patient = 0;
				for(int i = 0; i < count_patient; i++) {
					RomeBGroup(GetBGroup(i), GetBResult(i));
					cout << "Full name: " << GetFullName(i)
						 << "\nAge: " << GetAge(i)
						 << "\nBlood group: " << GetRomeBGroup() << ", " << GetTextBResult() << "\n\n";
				}
			}
		}

		void PrintInfoPatients(int index) {
			if(GetFullName(index) == "") {
				cout << "Such a patient does not exist!";
				empty_patient = 1;
			} else {
				empty_patient = 0;

				RomeBGroup(GetBGroup(index), GetBResult(index));
				cout << "Full name: " << GetFullName(index)
					 << "\nAge: " << GetAge(index)
					 << "\nBlood group: " << GetRomeBGroup() << ", " << GetTextBResult();
			}
		}

		void CreatePatient() {
			if(count_patient == 10) {
				cout << "Can't fit more patients!";
				empty_patient = 1;
			} else {
				empty_patient = 0;

				string text;
                int data;

				getline(cin, text);
				cout << "Full name: ";
				correctInput(text);
				SetFullName(count_patient, text);

				cout << "\nEnter a number between 18 and 120."
                     << "\nAge: ";
				correctNumberInput(data, 18, 120);
				SetAge(count_patient, data);

				cout << "\nEnter a number, from 1 to 4."
                     << "\nBlood group: ";
				correctNumberInput(data, 1, 4);
				SetBGroup(count_patient, data);

				cout << "\nNegative(0)/Positive(1): ";
				correctNumberInput(data, 0, 1);
				SetBResult(count_patient, data);

                count_patient++;
			}
		}

		void EditPatient(int index) {
			if(GetFullName(index) == "") {
				cout << "Such a patient does not exist!";
				empty_patient = 1;
			} else {
				empty_patient = 0;

				string text;
                int data;

				cout << "Old data:\n\n";
                    PrintInfoPatients(index);
				cout << "\n\n";

                getline(cin, text);
				cout << "Full name: ";
				correctInput(text);
				SetFullName(index, text);

				cout << "\nEnter a number between 18 and 120."
                     << "\nAge: ";
				correctNumberInput(data, 18, 120);
				SetAge(index, data);

				cout << "\nEnter a number, from 1 to 4."
                     << "\nBlood group: ";
				correctNumberInput(data, 1, 4);
				SetBGroup(index, data);

				cout << "\nNegative(0)/Positive(1): ";
				correctNumberInput(data, 0, 1);
				SetBResult(index, data);
			}
		}

		void DeletePatient(int index) {
			if(index > count_patient || count_patient == 0) {
				empty_patient = 1;
			} else {
				empty_patient = 0;

				for(int i = index; i < count_patient; ++i) {
					if(i >= count_patient) {
						fullname[i] = "";
					} else {
						fullname[i] = fullname[i + 1];
						age[i] = age[i + 1];
						bgroup[i] = bgroup[i + 1];
						bresult[i] = bresult[i + 1];
					}
				}
				count_patient--;
				if(count_patient == 0) { empty_patient = 1; }
			}
		}

		~Patients() {}
};

class Rooms {
	protected:
		int amount_room[10];
	public:
		Rooms() {
			for (int i = 0; i < 10; ++i) amount_room[i]=i;
		}

		int GetAmRoom(int num) { return amount_room[num]; }

		void PrintRooms() { for(int i = 0; i < 10; i++) cout << "Ward №" << amount_room[i]+1 << "\n"; }
};

class Medics: public Patients, public Rooms {
		string medics_name[10], medics_hp[10], meds_patient[10], patient_plague[10];
		int empty_medics;
	public:
		Medics() {
			medics_name[0] = "Igor Vertepa";
			medics_hp[0] = medics_name[0];
			meds_patient[0] = fullname[0];
			patient_plague[0] = "";

			count_medics = 1;
			count_keepRoom = 1;
		}

		string MedicsName(int index)     { return medics_name[index];    }
		string MedsHp(int index)         { return medics_hp[index];      }
		string MedsPatient(int index)    { return meds_patient[index];   }
		string Patient_Plague(int index) { return patient_plague[index]; }
		int    GetEmptyMed()		     { return empty_medics;		     }

        Medics & Delete_MedsPatient(int index)   { meds_patient[index] = ""; }
        Medics & Delete_MedsHp(int index)  	     { medics_hp[index] = "";    }

		Medics & Set_MedicsName(int index, string text)    { medics_name[index]  = text;  						  }
		Medics & Set_MedsHp(int index, string text)	   	   { medics_hp[index]    = text;    					  }
		Medics & Set_MedsPatient(int index, string text)   { meds_patient[index] = text; 					  	  }
		Medics & Set_NewMedicsName(int index, string text) { medics_name[index]  = text; medics_hp[index] = text; }
		Medics & SetMedicsKeep(int index, int index_medics, int index_patient) {
			meds_patient[index] = fullname[index_patient];
			medics_hp[index] = medics_name[index_medics];
		}
		Medics & Set_Patient_Plague(int index, string text) { patient_plague[index] = text; }

		void PrintMedics() {
			if(count_medics == 0) {
				cout << "There are no doctors. No one to treat the sick!";
				    empty_medics = 1;
			} else {
					empty_medics = 0;
					for(int i = 0; i < count_medics; i++) {
					if(MedicsName(i) == "") break;
					cout << i+1 << ". " << MedicsName(i) << "\n";
				}
			}
		}

		void PrintPatientKeep(int index) {
			if(MedsPatient(index) == "" || count_keepRoom == 0) {
				cout << "This room is empty, look at the other one.";
				empty_medics = 1;
			} else {
				empty_medics = 0;

				cout << "\tRoom number #" << GetAmRoom(index)+1 << "\n";
                if(MedsHp(index) == ""){
                    cout << "\nAt the moment, no doctor has been appointed.";
                } else {
                    cout << "\nDoctor: " << MedsHp(index) << ".";
                }
                cout << "\nSick: " << MedsPatient(index) << ".";
                if(Patient_Plague(index) != "") { cout << "\nSick: " << Patient_Plague(index) << "."; }
                else { cout << "\nAt the moment, not diagnosed with it."; }
			}
		}

		void CreatedMedics(){
			if(count_medics == 10) {
				cout << "No more doctors to hire! Not enough money to pay.";
				empty_patient = 1;
			} else {
				empty_patient = 0;
				string text;

				getline(cin, text);
				cout << "Full name: ";
				correctInput(text);

				Set_MedicsName(count_medics, text);
				count_medics++;
			}
		}

		void EditMedicsName(int index) {
			if(MedicsName(index) == ""){
				cout << "There is no such doctor!";
				empty_patient = 1;
			} else {
				string text;
				empty_patient = 0;

				cout << "\nOld data: " << MedicsName(index);

                getline(cin, text);
				cout << "\nEnter full name: ";
				correctInput(text);

				Set_NewMedicsName(index, text);
			}
		}

		void DeleteMedics(int index) {
			if(index > count_medics || count_medics == 0) {
				empty_medics = 1;
			} else {
				empty_medics = 0;

				for(long i = index; i < count_medics; ++i) {
					medics_name[i] = medics_name[i + 1];
				}
				count_medics--;
				if(count_medics == 0) empty_medics = 1;
			}
		}

		~Medics() {}
};

class Plague: public Medics {
	protected:
		string plague_list[10];
	public:
		Plague() {
			plague_list[0] = "Gastroduodenitis";
			plague_list[1] = "Bronchial asthma";
			plague_list[2] = "Diabetes mellitus";
			plague_list[3] = "Oncological diseases";
			plague_list[4] = "Hypertonic disease";
			plague_list[5] = "Ischemic heart disease";
			plague_list[6] = "Stroke";
			plague_list[7] = "Heart attack";
			plague_list[8] = "Phlebeurysm";
			plague_list[9] = "Acute respiratory viral infection";
		}

		string GetPlague(int index) { return plague_list[index]; }

		void PrintPlague() {
			for(int i = 0; i < 10; i++) {
				cout << i+1 << ". " << plague_list[i] << endl;
			}
		}

		~Plague() {}
};

class HistoryPlague {
	public:

};

int main(int argc, char* argv[]) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int age, bgroup, bresult;
	int index, index_plague, index_medics, check_patient, check;
	string name, choice, sub_choice;
	time_t t = time(0);
    tm * local = localtime(&t);

	Patients obj_patients;
	Medics obj_medics;
	Plague obj_plague;
	Rooms obj_rooms;
	//HistoryPlague obj_historyP;

	do {
		menu:
		system("cls");
		cout << "Welcome to Medical Incorporated!"
		     << "\nThe current date " << time_put(local, "%d/%m/%Y")
		     << "\n\n>1<. Patients."
		     << "\n>2<. Wards."
		     << "\n>3<. Doctors"
		     << "\n>0<. Exit."
		     << "\n\n>>> ";
		cin >> choice;
	} while(choice != "0" && choice != "1" && choice != "2" && choice != "3");

	if(choice == "0") { exit(0); 	   }
	if(choice == "1") { goto patients; }
	if(choice == "2") { goto rooms;    }
	if(choice == "3") { goto doctors;  }

///--------------Пацієнти------------------------------
	do {
		patients:
		system("cls");
		cout << ">1<. Register the patient."
		     << "\n>2<. List of patients."
		     << "\n>3<. File cabinet."
		     << "\n>0<. Return back."
		     << "\n\n>>> ";
		cin >> choice;
	} while(choice != "0" && choice != "1" && choice != "2" && choice != "3");

	if(choice == "0") goto menu;
	if(choice == "1") {
		do {
			system("cls");
			obj_patients.CreatePatient();

			cout << "\n>1<. Register another patient."
			     << "\n>0<. Back."
			     << "\n\n>>> ";
			cin >> choice;
		} while(choice != "0");
		if(choice == "0") { goto patients; }
	}
	if(choice == "2") {
		do {
			patients_edit:
			system("cls");
			obj_patients.PrintPatients();

			if(sub_choice == "1" && sub_menu != 1) {
                if(obj_patients.GetEmpty() == 1) {
                    cout << "\n>0<. Exit."
                         << "\n\n>>> ";
                } else {
                    cout << "\nEnter patient number (0 - return to menu): ";
                }
                correctNumberInput(index, 0, count_patient);
				index -= 1;
				if(index < 0 || obj_patients.GetEmpty() == 1) { sub_menu = 1; goto patients_edit; }

				//========
				system("cls");
				cout << "Old name: " << obj_patients.GetFullName(index)
				     << "\nEnter new: ";
				getline(cin, name, '\n');
				correctInput(name);
				for(check_patient = 0, check = 0; check_patient < count_keepRoom; check_patient++) {
                    if(obj_medics.MedsPatient(check_patient) == obj_patients.GetFullName(index)){
                    	check = 1;
						break;
					}
                }
                if(check == 1) {
                    obj_medics.Set_MedsPatient(check_patient, name);
				}
				obj_patients.SetFullName(index, name);

				do {
					cout << "\n>1<. Back to list."
					     << "\n>0<. Exit."
					     << "\n\n>>> ";
					cin >> choice;
				} while(choice != "0" && choice != "1");
				if(choice == "0") { sub_menu = 1; goto patients_edit; }
				if(choice == "1") { goto patients_edit;				  }
			}
			if(sub_choice == "2" && sub_menu != 1) {
                if(obj_patients.GetEmpty() == 1) {
                    cout << "\n>0<. Exit."
                         << "\n\n>>> ";
                } else {
                    cout << "\nEnter patient number (0 - return to menu):";
                }
                correctNumberInput(index, 0, count_patient);
				index -= 1;
				if(index < 0 || obj_patients.GetEmpty() == 1) { sub_menu = 1; goto patients_edit; }

				//========
				system("cls");
				for(check_patient = 0, check = 0; check_patient < count_keepRoom; check_patient++) {
                    if(obj_medics.MedsPatient(check_patient) == obj_patients.GetFullName(index)){
                    	check = 1;
						break;
					}
                }
                obj_patients.EditPatient(index);
                if(check == 1) {
                    obj_medics.Set_MedsPatient(check_patient, obj_patients.GetFullName(index));
				}

				do {
					cout << "\n>1<. Back to list."
					     << "\n>0<. Exit."
					     << "\n\n>>> ";
					cin >> choice;
				} while(choice != "0" && choice != "1");
				if(choice == "0") { sub_menu = 1; goto patients_edit; }
				if(choice == "1") { goto patients_edit; 			  }
			}
			if(sub_choice == "3" && sub_menu != 1) {
                if(obj_patients.GetEmpty() == 1) {
                    cout << "\n>0<. Exit."
                         << "\n\n>>> ";
                } else {
                    cout << "\nEnter patient number (0 - return to menu): ";
                }
                correctNumberInput(index, 0, count_patient);
				index -= 1;
				if(index < 0 || obj_patients.GetEmpty() == 1) { sub_menu = 1; goto patients_edit; }
				//========
				system("cls");
				for(check_patient = 0, check = 0; check_patient < count_keepRoom; check_patient++) {
                    if(obj_medics.MedsPatient(check_patient) == obj_patients.GetFullName(index)){
                    	check = 1;
						break;
					}
                }
                if(check == 1) {
                    obj_medics.Delete_MedsPatient(check_patient);
                    obj_medics.Delete_MedsHp(check_patient);
                    count_keepRoom--;
				}
				obj_patients.DeletePatient(index);

				do {
					system("cls");
					if(obj_patients.GetEmpty() == 0) {
						cout << "The patient was successfully discharged.";
					} else {
						cout << "Unfortunately, but for some reason, the patient refused to be discharged.";
					}

					cout << "\n\n>1<. Back to list."
					     << "\n>0<. Exit."
					     << "\n\n>>> ";
					cin >> choice;
				} while(choice != "0" && choice != "1");
				if(choice == "0") { sub_menu = 1; goto patients_edit; }
				if(choice == "1") { goto patients_edit;				  }
			}
			sub_menu = 1;
			if(sub_menu == 1) {
				cout << "\n>1<. Edit the patient's name."
				     << "\n>2<. Edit patient information."
				     << "\n>3<. Release the patient."
				     << "\n>0<. Exit."
				     << "\n\n>>> ";
				cin >> sub_choice;
				sub_menu = 0;
			}
		} while(sub_choice != "0");

		if(sub_choice == "0" && sub_menu == 0) { goto patients;	}
	}
	if(choice == "3") {
		system("cls");
		obj_patients.PrintInfoPatients();
		cout << "\n";
		system("pause");
		goto patients;
	}

///--------------Лікарняні палати-------------------------------
	do {
		rooms:
		system("cls");
		cout << ">1<. List of wards."
		     << "\n>0<. Exit."
		     << "\n\n>>> ";
		cin >> choice;
	} while(choice != "0" && choice != "1");

	if(choice == "0") { goto menu; }
	if(choice == "1") {
		do {
			rooms_list:
			system("cls");
			obj_rooms.PrintRooms();

			//------
			if(sub_choice == "1" && sub_menu != 1) {
                cout << "\nEnter the room number (0 - return to the menu): ";
                correctNumberInput(index, 0, 10);
				index -= 1;
				if(index < 0) { sub_menu = 1; goto rooms_list; }
				//-----
				do {
                    patient_room:
					system("cls");
					obj_medics.PrintPatientKeep(index);

					if(obj_medics.MedsHp(index) != "" && obj_medics.MedsPatient(index) != ""){
                        cout << "\n\n>1<. View another room."
                         << "\n>2<. Prescribe a diagnosis"
					     << "\n>0<. Exit."
					     << "\n\n>>> ";
                        cin >> choice;
					} else {
                        cout << "\n\n>1<. View another room."
					     << "\n>0<. Exit."
					     << "\n\n>>> ";
                        cin >> choice;
					}
				} while(choice != "0" && choice != "1" && choice != "2");
                    if(choice == "0") { sub_menu = 1; goto rooms_list; }
                    if(choice == "1") { goto rooms_list; 	  	  }
                    if(choice == "2" && obj_medics.GetEmptyMed() == 0){
                        system("cls");
                        obj_plague.PrintPlague();

                        cout << "\nEnter the number of the disease (0 - exit): ";
                        correctNumberInput(index_plague, 0, 10);
                        index_plague -= 1;
                        if(index_plague < 0) { goto patient_room; }

                        obj_medics.Set_Patient_Plague(index, obj_plague.GetPlague(index_plague));
                        goto patient_room;
                } else { goto patient_room; }
			}
			sub_menu = 1;
			if(sub_menu = 1) {
				cout << "\n>1<. Enter the room number."
				     << "\n>0<. Back."
				     << "\n\n>>> ";
				cin >> sub_choice;
				sub_menu = 0;
			}
		} while(sub_choice != "0");
		if(sub_choice == "0") { goto rooms; }
	}

///--------------Лікарі---------------------------
	do {
		doctors:
		system("cls");
		cout << ">1<. List of current doctors."
		     << "\n>2<. Attending doctor."
		     << "\n>3<. Reluctantly, fire the doctor."
		     << "\n>0<. Exit."
		     << "\n\n>>> ";
		cin >> choice;
	} while(choice != "0" && choice != "1" && choice != "2" && choice != "3");

	if(choice == "0") { goto menu; }
	if(choice == "1") {
		do{
			medics_list:
			system("cls");
			obj_medics.PrintMedics();

			if(sub_choice == "1" && sub_menu != 1){
				system("cls");
				obj_medics.CreatedMedics();

				do{
					cout << "\n>1<. Hire another doctor."
						 << "\n>0<. Exit."
						 << "\n\n>>> ";
					cin >> choice;
				} while(choice != "0" && choice != "1");
				if(choice == "0") { sub_menu = 1; goto medics_list; }
				if(choice == "1") { goto medics_list; 	  	 	 	}
			}
			if(sub_choice == "2" && sub_menu != 1 && obj_medics.GetEmptyMed() == 0){
                cout << "\nEnter the number of the doctor (0 - return to the menu):";
                correctNumberInput(index, 0, count_medics);
				index -= 1;
				if(index < 0) { sub_menu = 1; goto medics_list; }

				for(check_patient = 0, check = 0; check_patient < count_medics; check_patient++) {
                    if(obj_medics.MedsHp(check_patient) == obj_medics.MedicsName(index)){
                    	check = 1;
						break;
					}
                }
                obj_medics.EditMedicsName(index);
                if(check == 1) {
                    obj_medics.Set_MedsHp(check_patient, obj_medics.MedicsName(index));
				}

				do{
					cout << "\n\n>1<. Back to list."
						 << "\n>0<. Exit."
						 << "\n\n>>> ";
					cin >> choice;
				} while(choice != "0" && choice != "1");
				if(choice == "0") { sub_menu = 1; goto medics_list; }
				if(choice == "1") { goto medics_list;				}
			}
			sub_menu = 1;
			if(sub_menu = 1) {
                if(obj_medics.GetEmptyMed() == 0) {
                    cout << "\n>1<. Get a new doctor."
                         << "\n>2<. Edit doctor's name."
                         << "\n>0<. Back."
                         << "\n\n>>> ";
                    cin >> sub_choice;
                } else {
                    cout << "\n\n>1<. Get a new doctor."
                         << "\n>0<. Back."
                         << "\n\n>>> ";
                    cin >> sub_choice;
                }
				sub_menu = 0;
			}
		} while(sub_choice != "0");
		if(sub_choice == "0") { goto doctors; }
	}
	if(choice == "2") {
		_doctors:
		system("cls");
		if(obj_medics.MedicsName(0) == "" && obj_medics.MedsHp(0) == ""){
            cout << "You do not have doctors to prescribe them to the patient!\n\n";
            system("pause"); goto doctors;
		} else {
            if(count_medics == 10){
                cout << "No more wards! Write someone out.";
            } else {
                system("cls");
                obj_patients.PrintPatients();
                cout << "\nEnter patient number (0 - return to menu): ";
                correctNumberInput(index, 0, count_patient);
                index -= 1;
                if(index < 0) { goto doctors; }
                for(check_patient = 0, check = 0; check_patient < count_keepRoom; check_patient++) {
                    if(obj_medics.MedsPatient(check_patient) == obj_patients.GetFullName(index)) {
                    	check = 1;
						break;
					}
                }
                if(check == 1) {
                    do{
                        system("cls");
                        cout << "This patient already has an attending physician! Would you like to change?"
                             << "\n\n>1<. Yes."
                             << "\n>0<. No."
                             << "\n\n>>> ";
                        cin >> choice;
                    } while(choice != "0" && choice != "1");
                    if(choice == "1") { count_keepRoom--; }
                    if(choice == "0") { goto _doctors;    }
                }
                if(index < 0) { goto doctors; }

                //next:
                system("cls");
                obj_medics.PrintMedics();
                cout << "\nEnter the number of the doctor (0 - return to the menu): ";
                correctNumberInput(index_medics, 0, count_medics);
                index_medics -= 1;
                if(index_medics < 0) { goto doctors; }

                obj_medics.SetMedicsKeep(count_keepRoom, index_medics, index);
                count_keepRoom++;
            }

            do {
                system("cls");
                cout << ">1<. Book another doctor."
                     << "\n>0<. Exit."
                     << "\n\n>>> ";
                cin >> choice;
            } while(choice != "0" && choice != "1");
            if(choice == "0") { goto doctors;  }
            if(choice == "1") { goto _doctors; }
		}
	}
	if(choice == "3") {
		delet_doctors:
		system("cls");
		obj_medics.PrintMedics();

        if(obj_medics.GetEmptyMed() == 1){
            cout << "\n\n>0<. Exit."
                  << "\n\n>>> ";
        } else {
            cout << "\nEnter the number of the doctor (0 - return to the menu): ";
        }
        correctNumberInput(index, 0, count_medics);
		index -= 1;
		if(index < 0 || obj_medics.GetEmptyMed() == 1) { goto doctors; }

		obj_medics.DeleteMedics(index);
		obj_medics.Delete_MedsHp(index);
		do {
			system("cls");
			cout << "For a long time you heard the cry of the doctor you fired.";

			cout << "\n\n>1<. Fire another doctor."
			     << "\n>0<. Exit."
			     << "\n\n>>> ";
			cin >> choice;
		} while(choice != "0" && choice != "1");
		if(choice == "0") { goto doctors;  		}
		if(choice == "1") { goto delet_doctors; }
	}
}
