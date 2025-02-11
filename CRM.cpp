#include "CRM.h"
#include <string>
#include <fstream>
#include <sstream>
#include <Windows.h>

ClientManagement::ClientManagement()
{
//	std::vector<Client*> vecList;
	ifstream file;
	file.open("clientlist.txt");
	if (!file.fail()) {
		while (!file.eof()) {
			vector<string> row = parseCSV(file, ',');	//vector曖 牖憮 釭援朝 晦遽擊 ','煎 撲薑
			if (row.size()) {
				int id = atoi(row[0].c_str());		//詭賅濰縑 盪濰腎橫氈朝 僥濠蒂 integer煎 夥脯憮 id縑 渠殮
				char gender = row[2][0];			//2廓簞 還縑 羅廓簞 旋濠蒂 gender縑 渠殮
				int age = atoi(row[3].c_str());
				Client* c = new Client(id, row[1], gender, age, row[4], row[5]);	
									//id, name, gender, age, phonenumber, adress 牖
				clientList_.insert({ id, c });
//				vecList.push_back(c);
			}
		}
	}
	file.close();

/*	vector煎 匐儀
	int id = 2;
	string name = "Yuna";
	auto it = find_if(vecList.begin(), vecList.end(),
		[=](Client* p) { return *p == name; });
	if (it != vecList.end()) {
		Client* c = *it;
		c->displayInfo();
	}
*/
}

ClientManagement::~ClientManagement()
{
	ofstream file;
	file.open("clientlist.txt");
	if (!file.fail()) {
		for (const auto& v : clientList_) {
			Client* c = v.second;
			if(c != nullptr) {
			file << c->id() << ','			// 堅偌 薑爾 牖憮渠煎 盪濰
				<< c->getName() << ','
				<< c->getGender() << ','
				<< c->getAge() << ','
				<< c->getPhoneNumber() << ','
				<< c->getAdress() << endl;
			}
		}
	}
	cout << "******堅偌 葬蝶お 盪濰 諫猿******" << endl;
	file.close();
}

vector<string> ClientManagement::parseCSV(istream& file, char delimiter)
{
	stringstream ss;
	vector<string> row;
	string t = " \n\r\t";

	//stringstream擊 檜辨ж罹 欽橫 釭援晦
	while (!file.eof()) {
		char c = file.get();
		if (c == delimiter || c == '\r' || c == '\n') {
			if (file.peek() == '\n') file.get();
			string s = ss.str();
			s.erase(0, s.find_first_not_of(t));
			s.erase(s.find_last_not_of(t) + 1);
			row.push_back(s);
			ss.str("");
			if (c != delimiter) break;
		}
		else {
			ss << c;
		}
	}
	return row;
}

int ClientManagement::makeID() {	//堅偌 ID 儅撩(map擎 濠翕薑溺, 醞犒 X 晦棟檜 氈晦 陽僥縑 
									//primary key蒂 虜菟晦縑 謠棻.
	auto key = clientList_.end();	//key縑 end()蒂 渠殮
	if (clientList_.size() == 0) {	
		return 10001;				//虜擒 堅偌 薑爾陛 橈棻賊 10001擊 奩��
	}
	else 
	{
		int id = (--key)->first;	//氈棻賊 棻擠 牖憮睡攪 id蒂 1噶 隸陛
		return ++id;
	}
}

void ClientManagement::cmInput()
{
	string name, phoneNumber, adress;
	char gender;
	int age = 1, flag = 0;

	//堅偌 薑爾 殮溘
	cout << "檜葷 : "; getline(cin, name, '\n');
	do { 
		if (flag == 1) 
		{ cout << endl << "!!撩滌擊 棻衛 殮溘ж撮蹂!!" << endl << endl; }					// flag ==1檜賊 轎溘
		cout << "撩滌(M/W) : ";  cin >> gender; gender = toupper(gender); flag = 1; }	
	while (gender != 'M' && gender != 'W');												// 撩滌擊 薯渠煎 嫡擊 陽梱雖 奩犒
	flag = 0;
	while (flag!=1) { cout << "釭檜 : "; Primary::integerInput(age, flag); }				// 薑熱陛 嬴棲賊 啗樓 奩犒
	cout << "瞪�食醽� : "; cin >> phoneNumber;
	cout << "輿模 : "; cin.ignore(); getline(cin, adress, '\n');
	
	int id = makeID();	//嬴檜蛤朝 濠翕 儅撩
	
	//堅偌 偌羹 翕瞳 詭賅葬 й渡(��縑 儅撩)
	Client* c = new Client(id, name, gender, age, phoneNumber, adress);

	clientList_[makeID()] = c; //map縑 key -> makeID() , value -> c 渠殮
							   //clientList_.insert({makeID(), c});
	
	cout << endl << "撩奢瞳戲煎 殮溘ц蝗棲棻." << endl << "濡衛�� 詭檣詭景煎 給嬴骨棲棻." << endl;
	Sleep(1000); Sleep(1000);
	system("cls");
	/*Client* client1 = new Client("TaeHun", 'M', 30, "010-5557-9957", "AnSan");
	clientList_[1] = client1;*/
}

void ClientManagement::cmOutput()
{			// map曖 籀擠睡攪 部梱雖 ж釭噶 轎溘
	cout << "式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式" << endl;
	for_each(clientList_.begin(), clientList_.end(),
		[](auto cm) {Client* c = cm.second;	//偌羹 薑爾(c)朝 map曖 value 薑爾(second)
		if (c != nullptr) {
			cout << "[" << c->id() << "] 檜葷: " << c->getName()		//ID 牖憮渠煎 堅偌 薑爾 轎溘
				<< " 撩滌: " << c->getGender() << " 釭檜: " << c->getAge()  
				<< " 瞪�食醽�: " << c->getPhoneNumber() << " 輿模: " << c->getAdress() << endl;
				// 偌羹曖 詹幗 л熱縑 蕾斬
			cout << "-----------------------------------------------------------------------------" << endl;
			}
		}
	);													

	//for (auto i = clientList_.begin(); i != clientList_.end(); i++) {
	//	cout << i->first << " " << i->second->getName() << endl;
	//}
}

Client* ClientManagement::cmChooseID(int id) //id高 奩��
{
	auto it = clientList_.find(id);
	return (it != clientList_.end())? clientList_[id] : nullptr;
}

void ClientManagement::cmSearchID(int id) //ID煎 匐儀
{
	char one;
	Client* c = clientList_[id];				//匐儀й ID 殮溘

	if (clientList_.find(id)==clientList_.end())						//ID陛 橈戲賊 轎溘
	{
		cout << endl;
		cout << endl << "\t\t" << "************************************" << endl;
		cout << "\t\t" << "!!襄營ж雖 彊朝 堅偌殮棲棻!!" << endl;
		cout << "\t\t" << "!!濡衛�醴� 詭檣 詭景煎 給嬴骨棲棻!!" << endl;
		cout << endl << "\t\t" << "************************************" << endl;
		Sleep(1000); Sleep(1000);
		system("cls");
	}

	else {
		cout << "式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式" << endl
			<< id << " 堅偌 薑爾" << endl
			<< "式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式" << endl;
		cout << "檜葷: " << c->getName() << " 釭檜: "			//匐儀и ID 薑爾 轎溘
			<< c->getAge() << " 瞪�食醽�: "
			<< c->getPhoneNumber() << " 輿模: "
			<< c->getAdress() << endl;

		cout << endl << endl << "\t" << "嬴鼠酈釭 殮溘ж賊 詭檣�飛橉虞� 給嬴骨棲棻." << endl;
		one = _getch();
		system("cls");
		cin.ignore();
	}
}

void ClientManagement::cmSearchName() //檜葷戲煎 匐儀
{
	int found=0;		//釭醞縑 檜葷檜 襄營ж朝雖 �挫恉炱� 嬪п 餌辨
	char one;
	string name;		//匐儀й 檜葷
	string cmp_name;	//偌羹縑憮 �挫恉� 檜葷

	cout << "匐儀й 檜葷擊 殮溘ж撮蹂. "; cin >> name;
	cout << "式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式" << endl;

	//map曖 籀擠睡攪 部梱雖 匐儀
	for (auto i = clientList_.begin(); i != clientList_.end(); i++) {
		if(i->second != nullptr)
			cmp_name = i->second->getName();
		if((cmp_name == name)) {		//匐儀и 檜葷曖 堅偌檜 氈棻賊 醞犒п憮 賅舒 匐儀
			found = 1;
			cout << "檜葷: " << i->second->getName() << " 釭檜: "
				<< i->second->getAge() << " 瞪�食醽�: "
				<< i->second->getPhoneNumber() << " 輿模: "
				<< i->second->getAdress() << endl;
			cout << "-----------------------------------------------------------------------------" << endl;
		}
		cmp_name = ""; //string 蟾晦��
	} 

	if (found == 0) {
		cout << endl;
		cout << endl << "\t\t" << "************************************" << endl;
		cout << "\t\t" << "!!瓊朝 檜葷檜 橈蝗棲棻!!" << endl;
		cout << "\t\t" << "!!濡衛�醴� 詭檣 詭景煎 給嬴骨棲棻!!" << endl;
		cout << endl << "\t\t" << "************************************" << endl;
		Sleep(1000); Sleep(1000);
		system("cls");
	}
	else {
		cout << endl << endl << "\t" << "嬴鼠酈釭 殮溘ж賊 詭檣�飛橉虞� 給嬴骨棲棻." << endl;
		one = _getch();
		system("cls");
		cin.ignore();
	}
}

//薑爾 餉薯
void ClientManagement::deleteClient(int id) {

	if(clientList_.find(id)==clientList_.end()) {			// 瓊朝 嬴檜蛤陛 橈戲賊 轎溘
		cout << endl;
		cout << endl << "\t\t" << "************************************" << endl;
		cout << "\t\t" << "!!襄營ж雖 彊朝 堅偌殮棲棻!!" << endl;
		cout << "\t\t" << "!!濡衛�醴� 詭檣 詭景煎 給嬴骨棲棻!!" << endl;
		cout << endl << "\t\t" << "************************************" << endl;
		Sleep(1000); Sleep(1000);
	}
	else {
		clientList_.erase(id);			// erease煎 key 餉薯
		cout << endl << "\t\t" << "式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式" << endl;
		cout << "\t\t" << "!!撩奢瞳戲煎 薯剪 腎歷蝗棲棻!!" << endl;
		cout << "\t\t" << "!!濡衛�醴� 詭檣 詭景煎 給嬴骨棲棻!!" << endl;
		cout << endl << "\t\t" << "式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式" << endl;
		Sleep(1000); Sleep(1000);
	}
	getchar();
}

//薑爾 滲唳
void ClientManagement::cmRevise(int id) {

	Client* c = clientList_[id];

	if (!(clientList_[id])) {			// 瓊朝 嬴檜蛤陛 橈戲賊 轎溘
		cout << endl;
		cout << endl << "\t\t" << "************************************" << endl;
		cout << "\t\t" << "!!襄營ж雖 彊朝 堅偌殮棲棻!!" << endl;
		cout << "\t\t" << "!!濡衛�醴� 詭檣 詭景煎 給嬴骨棲棻!!" << endl;
		cout << endl << "\t\t" << "************************************" << endl;
		Sleep(1000); Sleep(1000);
	}

	else {
		cout << "檜葷: " << c->getName() << " 釭檜 : "		//瓊朝 ID縑 渠и 薑爾 轎溘
			<< c->getAge() << " 瞪�食醽�: "
			<< c->getPhoneNumber() << " 輿模: "
			<< c->getAdress() << endl << endl;

		int num, age; char one;
		string name, phoneNumber, adress;
		cout << "式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式" << endl;
		cout << "            夥紱堅 談擎 薑爾蒂 殮溘ж撮蹂.            " << endl;
		cout << "1: 檜葷   |   2: 釭檜   |   3: 瞪�食醽�   |   4: 輿模   |   0: 鏃模" << endl;
		Primary::switchInput(num, one); cout << endl;

		//夥紱堅 談擎 薑爾縑 評塭 switch 僥 褒ч
		switch (num) {
		case 1:		//檜葷 滲唳
			cout << "檜葷 : "; cin.ignore(); getline(cin, name, '\n');
			c->setName(name);
			break;
		case 2:		//釭檜 滲唳
			cout << "釭檜 : "; cin >> age;
			c->setAge(age);
			break;
		case 3:		//瞪�食醽� 滲唳
			cout << "瞪�食醽� : "; cin >> phoneNumber;
			c->setPhoneNumber(phoneNumber);
			break;
		case 4:		//輿模 滲唳
			cout << "輿模 : "; cin.ignore(); getline(cin, adress, '\n');
			c->setAdress(adress);
			break;
		default:
			getchar();
			system("cls");
			break;
		}
		if (0 < num && num < 5) {
			cout << endl << "\t\t" << "式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式" << endl;
			cout << "\t\t" << "!!撩奢瞳戲煎 滲唳 腎歷蝗棲棻!!" << endl;
			cout << "\t\t" << "!!濡衛�醴� 詭檣 詭景煎 給嬴骨棲棻!!" << endl;
			cout << endl << "\t\t" << "式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式" << endl;
			Sleep(1000); Sleep(1000); system("cls");
		}
	}
}

void ClientManagement::showList() {
	for (auto cm : clientList_) {
		Client* c = cm.second;
		if (c != nullptr) {
			cout << "[" << c->id() << "] 檜葷: " << c->getName()		//匐儀и ID 薑爾 轎溘
				<< " 撩滌: " << c->getGender() << " 釭檜: " << c->getAge()
				<< " 瞪�食醽�: " << c->getPhoneNumber() << " 輿模: " << c->getAdress() << endl;
			cout << "-----------------------------------------------------------------------------" << endl;
		}
	}
}