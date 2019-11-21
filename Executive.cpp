#include<string>
#include<fstream>
#include<iostream>
#include <vector>
#include <regex>
#include <algorithm>

using namespace std;

class menu
{
  public:
    // variables
    string filepath;    // filepath
    vector< vector<string> > records;    //data matrix
    string NumberRec;    // number of records

    // functions
    void setfilepath( string fil );
    void readfile();
    void run();
};

// define each function
void menu::setfilepath( string fil ){
  filepath = fil;
};

//split an std::string into a vector<string>
vector<string> StrToVector(string TheLine)
{
	std::string s = TheLine;
	std::regex regex("\\	");

	std::vector<std::string> out(
					std::sregex_token_iterator(s.begin(), s.end(), regex, -1),
					std::sregex_token_iterator()
					);

  /*for (auto &s: out) { // output vector elements
		std::cout << s << '\n';
	}    */

	return out;
}

void menu::readfile (){

  string line;                              //this will contain the data read from the file
  ifstream myfile (filepath);               //opening the file.
  if (myfile.is_open())                     //if the file is open
  {

    int id = 0;
    while (! myfile.eof() )                 //while the end of file is NOT reached
    {
      getline (myfile,line);                //get one line from the file

      if (id == 0){    //Avoid the first line and store the total number of the record.
        cout << "Total number of records: " << line <<"\n";
        NumberRec = line;
        id = id+1;
        continue;
      };

      vector<string> Vecline = StrToVector(line);
      Vecline.push_back( to_string(id) );    // insert id to the first elements
      //cout << "The size is " << lineVec.size() <<  endl;                //the vector size
      int VecLen = Vecline.size();
      if (VecLen == 6) {
        records.push_back(Vecline);
      };

      id = id+1;
    }
    myfile.close();                         //closing the file
  }
  else cout << "Unable to open file";       //if the file is not open output
};

// define run function
void menu::run(){

  int choice;
  string team;
  int lowrank;
  int highrank;
  string tier;
  string playername;
  string player;
  int place;
  bool gameOn = true;
  while (gameOn != false){
  cout << "*******************************\n";
  cout << " 1 - Print all RBs sorted by ranking\n";
  cout << " 2 - Print all RBs from given team\n";
  cout << " 3 - Obtain a ranking range (e.g. 1 - 10) from the user\n";
  cout << " 4 - Print a tier\n";
  cout << " 5 - Edit a ranking\n";
  cout << " 6 - Exit\n";
  cout << " Enter your choice and press return: ";

  cin >> choice;

  switch (choice)
  {
    /*
    1 - Print all RBs sorted by ranking
    The order they appear will be the same order they appeared in the file
    Reminder, the file is presorted by ranking */
    case 1:
    {cout << "Print all RBs sorted by ranking\n";
    for (int i=0; i < records.size(); ++i){
      for (int j=0; j < records[i].size(); ++j) {
        cout << records[i][j] << ' ';
        }
      cout << endl;
      };
    break;}

    /*
    2 - Print all RBs from given team
    Obtain a team (e.g. KC) from the user then print all RBs on that team
    Print a ranking range */
    case 2:{
      cout << "Given team?\n";
      cin >> team;
      //cout << team;
      vector< vector<string> > TeamRec;
      for (int i=0; i<records.size();++i){    // obtain choosen vector
        if (records[i][1]==team){ TeamRec.push_back(records[i]);};
      };
      cout << "Here are all RBs on the team\n";
      for (int i=0; i < TeamRec.size(); ++i){    // print choosen vector
        for (int j=0; j < TeamRec[i].size(); ++j) {
          cout << TeamRec[i][j] << ' ';
          }
        cout << endl;
      };


      vector<int> RanRange;
      for (int i=0; i<TeamRec.size(); ++i){    //print ranking range
        int Ranks = stoi(TeamRec[i][5]);
        //cout << Ranks;
        RanRange.push_back(Ranks);
      }

      if (RanRange.size()==0){
        cout << "No range available.\n";
      }
      else {
        cout << "The ranking range is:\n"
        << *min_element(begin(RanRange), end(RanRange)) << " to " << *max_element(begin(RanRange), end(RanRange)) << endl;;
      }
      break;
    }

    /*
    3 - Obtain a ranking range (e.g. 1 - 10) from the user and print all RBs in that ranking range
    Reminder, the file is presorted */
    case 3:
    {
      cout << "Lower bound of ranking?\n";
      cin >> lowrank;
      cout << "Higher boung of ranking?\n";
      cin >> highrank;

      vector< vector< string > > partRB;
      cout << "The selected RBs are: " << endl;
      for (int i=lowrank-1; i<highrank; ++i){
        partRB.push_back(records[i]);
      }
      for (int i=0; i < partRB.size(); ++i){    // print choosen vector
        for (int j=0; j < partRB[i].size(); ++j) {
          cout << partRB[i][j] << ' ';
          }
        cout << endl;
      };
      break;
    }

    /*
    4 - Print a tier
    Obtain a tier (single value 1 to 9) and print all RBs in that tier */
    case 4:{
      cout << "Which tier would you like?\n";
      cin >> tier;
      cout << "The selected RBs are:" << endl;
      vector< vector< string > > tierRB;
      for (int i=0; i<records.size();++i){
        if (tier==records[i][4]){
          tierRB.push_back(records[i]);
        };
      }
      for (int i=0; i < tierRB.size(); ++i){    // print choosen vector
        for (int j=0; j < tierRB[i].size(); ++j) {
          cout << tierRB[i][j] << ' ';
          }
        cout << endl;
      };
      break;
    }

    /*
    5 - Edit a ranking
    Obtain a player name from the user (if the name isn't in the list print a sensible error message)Give the user the choice to move the player up or down in the rankings and adjust the rankings accordingly. Be aware, this means swapping and editing the players around the chosen player. If the user then chooses print the players by rankings, the list should reflect this change */
    case 5:{
      cout << "Which player are you looking for?";
      cin >> player;
      bool isNameinList = false;
      for (int i = 0; i<records.size(); ++i){
        if (player==records[i][0]){isNameinList = true;}
      }
      if (isNameinList==false) {
        cout << "Can't find player!\n";
        break;
      } else {
        cout << "Position for changing rank?";
        cin >> place;
      }
      break;
    };


    /*6 - Exit the program */
    case 6:
    {cout << "End of Program.\n";
    gameOn = false;
    break;}

    default:
    {cout << "Not a Valid Choice. \n";
    cout << "Choose again.\n";
    cin >> choice;
    break;}
  }

  }

}
