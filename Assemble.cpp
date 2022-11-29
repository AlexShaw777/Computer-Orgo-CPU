#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>


using namespace std;
//This method takes the chunked binary code and pushes it into a vector of strings  
vector<string> chunktoHex (const string &s, char delimiter) {
  vector<string> ending;
  stringstream ss (s);
  string item;

  while (getline (ss, item, delimiter)) {
    ending.push_back (item);
  }
  return ending;
}
//this method is used to convert from decimal to binary 
//cited this method in pdf file 
string IntegerToString2sComp(int Integer){
	if (Integer < -32768 || Integer>32767){
    return "";
  }
	string result;
	for (int bit = 0; bit < sizeof(int) * 4; ++bit)
	{
		int bit_val = 1 & Integer;
		result = (bit_val ? "1" : "0") + result;
		Integer = Integer >> 1;
	}
	return result;
}
string IntegerToString2sComp_26_bit(int Integer){
	if (Integer < -32768 || Integer>32767){
    return "";
  }
	string result;
	for (int bit = 0; bit < 26; ++bit)
	{
		int bit_val = 1 & Integer;
		result = (bit_val ? "1" : "0") + result;
		Integer = Integer >> 1;
	}
	return result;
}
string IntegerToString2sComp_5_bit(int Integer){
	if (Integer < -32768 || Integer>32767){
    return "";
  }
	string result;
	for (int bit = 0; bit < 5; ++bit)
	{
		int bit_val = 1 & Integer;
		result = (bit_val ? "1" : "0") + result;
		Integer = Integer >> 1;
	}
	return result;
}

int main(int argc, char* argv[]){
  //Hash Map for registers 
  map<string, string> m;
  m["$zero"] = "00000";
  m["$at"] = "00001";
  m["$v0"] = "00010";
  m["$v1"] = "00011";
  m["$a0"] = "00100";
  m["$a1"] = "00101";
  m["$a2"] = "00110";
  m["$a3"] = "00111";
  m["$t0"] = "01000";
  m["$t1"] = "01001";
  m["$t2"] = "01010";
  m["$t3"] = "01011";
  m["$t4"] = "01100";
  m["$t5"] = "01101";
  m["$t6"] = "01110";
  m["$t7"] = "01111";
  m["$s0"] = "10000";
  m["$s1"] = "10001";
  m["$s2"] = "10010";
  m["$s3"] = "10011";
  m["$s4"] = "10100";
  m["$s5"] = "10101";
  m["$s6"] = "10110";
  m["$s7"] = "10111";
  m["$t8"] = "11000";
  m["$t9"] = "11001";
  m["$k0"] = "11010";
  m["$k1"] = "11011";
  m["$gp"] = "11100";
  m["$sp"] = "11101";
  m["$fp"] = "11110";
  m["$ra"] = "11111";
  m["$0"] = "00000";
  m["$1"] = "00001";
  m["$2"] = "00010";
  m["$3"] = "00011";
  m["$4"] = "00100";
  m["$5"] = "00101";
  m["$6"] = "00110";
  m["$7"] = "00111";
  m["$8"] = "01000";
  m["$9"] = "01001";
  m["$10"] = "01010";
  m["$11"] = "01011";
  m["$12"] = "01100";
  m["$13"] = "01101";
  m["$14"] = "01110";
  m["$15"] = "01111";
  m["$16"] = "10000";
  m["$17"] = "10001";
  m["$18"] = "10010";
  m["$19"] = "10011";
  m["$20"] = "10100";
  m["$21"] = "10101";
  m["$22"] = "10110";
  m["$23"] = "10111";
  m["$24"] = "11000";
  m["$25"] = "11001";
  m["$26"] = "11010";
  m["$27"] = "11011";
  m["$28"] = "11100";
  m["$29"] = "11101";
  m["$30"] = "11110";
  m["$31"] = "11111";

  // error if invalid arguments
  if (argc !=3){
    cerr << "Incorrect number of command line arguments " << endl;
    exit(1);
  }

  // open the input file for reading
  ifstream infile1(argv[1]);

  if (!infile1){
    // if file can't be opened, need to let the user know
    std::cerr << "Error: could not open file: " << argv[1] << std::endl;
    std::exit(1);
  }
  //open the output file for writing 
  ofstream outfile(argv[2]);

  if (!outfile){ //error in the case of file not opening
    std::cerr << "Error: could not open file: " << argv[2] << std::endl;
    std::exit(1);
  }

  // string label; 
  // string colon;
  // map<string, int> labelmap;

  // int instructioncounter = 0;
  // while (infile >> label){
  //   instructioncounter++;
  //   label.erase(label.length()-1);
  //   labelmap[label] = instructioncounter;
  // }
  // std::cout << instructioncounter;

  //All the instance variables used in the next section
  string binary;
  string function;
  string rs;
  string target;
  string rt;
  string rd;
  string sa;
  string address;
  string offset;
  string immediate;
  string at;
  int count = -1;
  int index = 0;
  

  //A vector of strings for our binary collection
  vector< string > binaryCollection;

  while (infile1.eof()!= true){
    infile1 >> function;
    if(function.front() == '.' || function == "main:"){
      continue;
    }
    if (function.back() == ':' ){
      function.erase(function.length()-1);
      m[function] = to_string(count+1);
    }
    if(function == "add"){
      infile1 >> rd >> rs >> rt;
      count++;
    }
    else if(function == "sub"){
      infile1 >> rd >> rs >> rt;
      count++;
      }
    //
    else if(function == "mult"){
        infile1 >> rs >> rt;
        count++;
    }

    else if(function == "div"){
        infile1 >> rs >> rt;
        count++;
      }
    else if(function == "mflo"){
        infile1 >> rd;
        count++;
      }
    else if(function == "mfhi"){
        infile1 >> rd;
        count++;
      }
    else if(function == "sll"){
      infile1 >> rd >> rt >> sa;
      count++;

    }
    else if(function == "srl"){
      infile1 >> rd >> rt >> sa;
      count++;

    }
    else if(function == "slt"){
      infile1 >> rd >> rs >> rt;
      count++;
    }
    else if(function == "sgt"){     //sgt bonus point 
      infile1 >> rd >> rt >> rs;
      count++;
    }
    else if(function == "sge"){     //sge bonus point 
      infile1 >> rd >> rs >> rt;
      count++;
    }
    else if(function == "sle"){     //sle bonus point 
      infile1 >> rd >> rs >> rt;
      count++;
    }
    else if(function == "seq"){     //seq bonus point 
      infile1 >> rd >> rs >> rt;
      count++;
    }
    else if(function == "sne"){     //sne bonus point 
      infile1 >> rd >> rs >> rt;
      count++;
    }
    if(function == "j"){
      infile1 >> target;
      count++;

    }
    if(function == "jal"){
      infile1 >> target;
      count++;
    }
    else if(function == "jr"){
      infile1 >> rs;
      count++;
    }
    else if(function == "jalr"){
      infile1 >> rd >> rs;
      count++;
    }
    else if(function == "syscall"){
      count++;
    }
    else if(function == "lw"){
      infile1 >> rt >> address;
      count++;
    }
    else if(function == "li"){     //li bonus point 
      infile1 >> rd >> immediate;
      count++;
    }
    else if(function == "sw"){
      infile1 >> rt >> address;
      count++;
    }
    else if(function == "addi"){
      infile1 >> rt >> rs >> immediate;
      count++;
    }
    else if(function == "beq"){
      infile1 >> rs >> rt >> offset;
      count++;
    }
    else if(function == "bne"){
      infile1 >> rs >> rt >> offset;
      count++;
    }
    else if(function == "bge"){     //bge bonus point 
      infile1 >> rd >> rs >> rt;
      count++;
    }
    else if(function == "blt"){     //blt bonus point 
      infile1 >> rd >> rs >> rt;
      count++;
    }
    else if(function == "ble"){     //ble bonus point 
      infile1 >> rd >> rs >> rt;
      count++;
    }
    else if(function == "bgt"){     //bgt bonus point 
      infile1 >> rd >> rs >> rt;
      count++;
    }
    else if(function == "mov"){     //mov bonus point
      infile1 >> rs >> rd;
      count++;
    }
    else if(function == "abs"){     //abs bonus point 
      infile1 >> rs >> rd;
      count++;
    }
    else if(function == "or"){     //abs bonus point 
      infile1 >> rd >> rs >> rt;
      count++;
    }
    else if(function == "and"){     //abs bonus point 
      infile1 >> rd >> rs >> rt;
      count++;
    }
    else if(function == "nor"){     //abs bonus point 
      infile1 >> rd >> rs >> rt;
      count++;
    }
    else if(function == "xor"){     //abs bonus point 
      infile1 >> rd >> rs >> rt;
      count++;
    }
  }
    infile1.close();

  ifstream infile(argv[1]);

  //a while loop to go line by line in the inputfile and attribute each function or non-function to its 
  //corresponding attributes 
  count = -1;
  while (infile >> function){
    index++;
    cout << function << " " << count << endl;
    if(function == "add"){
      count++;
      infile >> rd >> rs >> rt;
      rd.erase(rd.length()-1);
      rs.erase(rs.length()-1);
      binary = "000000"; //op code
      binary  += m[rs]; //s1: "10001";
      binary  += m[rt]; //s4: "10100";
      binary  += m[rd]; //t1: "01001";
      binary  += "00000"; // sa=00000
      binary  += "100000";// add=100000
      // cout << "add:  "<< binary << endl;
      binaryCollection.push_back(binary);
    }
    else if(function == "sub"){
      count++;
      infile >> rd >> rs >> rt;
      rd.erase(rd.length()-1);
      rs.erase(rs.length()-1);
      binary = "000000"; //op code
      binary  += m[rs]; //s1: "10001";
      binary  += m[rt]; //s4: "10100";
      binary  += m[rd]; //t1: "01001";
      binary  += "00000"; // sa=00000
      binary  += "100010";
      // cout << "sub:  " << binary << endl;
      binaryCollection.push_back(binary);
      }
    //
    else if(function == "mult"){
      count++;
      infile >> rs >> rt;
      rs.erase(rs.length()-1);
      binary = "000000";
      binary += m[rs];
      binary += m[rt];
      binary +="00000";
      binary +="00000";
      binary += "011000";
      // cout << "mult: "<< binary << endl;
      binaryCollection.push_back(binary);
    }


    else if(function == "div"){
        count++;
        infile >> rs >> rt;
        rs.erase(rs.length()-1);
        binary ="000000";
        binary += m[rs];
        binary += m[rt];
        binary +="00000";
        binary +="00000";
        binary += "011010";
        // cout << "div:  " << binary << endl;
        binaryCollection.push_back(binary);
      }
    else if(function == "mflo"){
        count++;
        infile >> rd;
        binary ="000000";
        binary += "00000";
        binary += "00000";
        binary += m[rd];
        binary +="00000";
        binary += "010010";
        // cout << "mflo: " << binary << endl;
        binaryCollection.push_back(binary);
      }
    else if(function == "mfhi"){
        count++;
        infile >> rd;
        binary ="000000";
        binary += "00000";
        binary += "00000";
        binary += m[rd];
        binary +="00000";
        binary += "010000";
        // cout <<"mfhi: "<< binary << endl;
        binaryCollection.push_back(binary);
      }
    else if(function == "sll"){
        count++;
        infile >> rd >> rt >> sa;
        rd.erase(rd.length()-1);
        rt.erase(rt.length()-1);
        binary = "000000";
        binary += "00000";
        binary += m[rt];
        binary += m[rd];
        binary += IntegerToString2sComp_5_bit(stoi(sa));
        binary += "000000";
        // cout <<"sll:  "<< binary << endl;
        binaryCollection.push_back(binary);

    }
    else if(function == "srl"){
      count++;
      infile >> rd >> rt >> sa;
      rd.erase(rd.length()-1);
      rt.erase(rt.length()-1);
      binary = "000000";
      binary += "00000";
      binary += m[rt];
      binary += m[rd];
      binary += IntegerToString2sComp_5_bit(stoi(sa));
      binary += "000010";
      // cout <<"srl:  "<< binary << endl;
      binaryCollection.push_back(binary);
    }
    else if(function == "slt"){
      count++;
      infile >> rd >> rs >> rt;
      rd.erase(rd.length()-1);
      rs.erase(rs.length()-1);
      binary = "000000"; //op code
      binary  += m[rs]; //s1: "10001";
      binary  += m[rt]; //s4: "10100";
      binary  += m[rd]; //t1: "01001";
      binary  += "00000"; // sa=00000
      binary  += "101010";
      cout << "slt:  "<<  binary << endl;
      binaryCollection.push_back(binary);
    }
    else if(function == "j"){
      count++;
      infile >> target;
      binary = "000010";
      binary += IntegerToString2sComp_26_bit(stoi(m[target]));
      // cout << "j:    "<<  binary << endl;
      binaryCollection.push_back(binary);
    }
    else if(function == "jal"){
      count++;
      infile >> target;
      binary = "000011";
      binary += IntegerToString2sComp_26_bit(stoi(m[target]));
      // cout << "jal:  "<<  binary << endl;
      binaryCollection.push_back(binary);
    }
    else if(function == "jr"){
      count++;
      infile >> rs;
      binary = "000000"; //op code
      binary += m[rs];
      binary += "00000";//rt
      binary += "00000";//rd
      binary  += "00000"; // sa=00000
      binary  += "001000";// jr=001000
      // cout << "jr:   "<<  binary << endl;
      binaryCollection.push_back(binary);
    }
    else if(function == "jalr"){
      count++;
      infile >> rd >> rs;
      rd.erase(rd.length()-1);
      binary = "000000"; //op code
      binary += m[rs];
      binary += "00000";//rt
      binary += m[rd];
      binary  += "00000"; // sa=00000
      binary  += "001001";// jalr=001001
      // cout << "jalr: "<<  binary << endl;
      binaryCollection.push_back(binary);
    }
    else if(function == "syscall"){
      count++;
      binary = "000000"; //op code
      binary += "00000"; //rs
      binary += "00000";//rt
      binary += "00000";//rd
      binary  += "00000"; // sa=00000
      binary  += "001100";// syscall=001100
      // cout << "syscall: "<<  binary << endl;
      binaryCollection.push_back(binary);
    }
    else if(function == "lw"){
      count++;
      infile >> rt >> address;
      rt.erase(rt.length()-1);
      rs = address.substr(address.find('(')+1, address.find(')'));
      rs.erase(rs.length()-1);
      binary = "100011"; //op code
      binary += m[rs]; // rs
      binary += m[rt];
      binary += IntegerToString2sComp(stoi(address.substr(0,address.find('('))));
      // cout << "lw:   "<<  binary << endl;
      binaryCollection.push_back(binary);
    }
    else if(function == "sw"){
      count++;
      infile >> rt >> address;
      rt.erase(rt.length()-1);
      rs = address.substr(address.find('(')+1, address.find(')'));
      rs.erase(rs.length()-1);
      binary = "101011"; //op code
      binary += m[rs]; // rs
      binary += m[rt];
      binary += IntegerToString2sComp(stoi(address.substr(0,address.find('('))));
      // cout << "sw:   "<<  binary << endl;
      binaryCollection.push_back(binary);
    }
    else if(function == "addi"){
      count++;
      infile >> rt >> rs >> immediate;
      rt.erase(rt.length()-1);
      rs.erase(rs.length()-1);
      binary = "001000";
      binary += m[rs]; // rs
      binary += m[rt];
      cout << immediate << " " << endl;
      binary += IntegerToString2sComp(stoi(immediate));
      // cout << "addi; "<<  binary << endl;
      binaryCollection.push_back(binary);
    }
    else if(function == "beq"){
      count++;
      infile >> rs >> rt >> offset;
      rt.erase(rt.length()-1);
      rs.erase(rs.length()-1);
      binary = "000100";
      binary += m[rs];
      binary += m[rt];
      cout << m[offset] << " " << offset << endl; 
      binary += IntegerToString2sComp((stoi(m[offset])) - (count+1));
      // cout << "beq;  "<<  binary << endl;
      binaryCollection.push_back(binary);
    }
    else if(function == "bne"){
      count++;
      infile >> rs >> rt >> offset;
      rt.erase(rt.length()-1);
      rs.erase(rs.length()-1);
      binary = "000101";
      binary += m[rs];
      binary += m[rt];
      binary += IntegerToString2sComp((stoi(m[offset])) - (count+1));
      // cout << "bne;  "<<  binary << endl;
      binaryCollection.push_back(binary);
    }
    else if(function == "sgt"){
      count++;
      // if();
      infile >> rd >> rs >> rt;
      rd.erase(rd.length()-1);
      rs.erase(rs.length()-1);
      binary = "000000"; //op code
      binary  += m[rt]; //s1: "10001";
      binary  += m[rs]; //s4: "10100";
      binary  += m[rd]; //t1: "01001";
      binary  += "00000"; // sa=00000
      binary  += "101010";
      cout << "sgt:  "<<  binary << endl;
      binaryCollection.push_back(binary);
    }
    else if(function == "sge"){
      count++;
      infile >> rd >> rs >> rt;
      rd.erase(rd.length()-1);
      rs.erase(rt.length()-1);
      binary = "000000";
      binary += m[rt];
      binary += m[rs];
      binary += m[rd];
      binary += "00000";
      binary += "101010";
      cout << "sge: " << binary << endl;
      binaryCollection.push_back(binary);
    }
    else if(function == "sle"){
      count++;
      infile >> rd >> rs >> rt;
      rd.erase(rd.length()-1);
      rs.erase(rt.length()-1);
      binary = "000000";
      binary += m[rs];
      binary += m[rt];
      binary += m[rd];
      binary += "00000";
      binary += "101010";
      cout << "sle: " << binary << endl;
      binaryCollection.push_back(binary);
    }
    else if(function == "seq"){
      count++;
      infile >> rd >> rs >> rt;
      rd.erase(rd.length()-1);
      rs.erase(rs.length()-1);
      binary = "000000"; //op code
      binary  += m[rs]; //s1: "10001";
      binary  += m[rt]; //s4: "10100";
      binary  += m[at]; //t1: "01001";
      binary  += "00000"; // sa=00000
      binary  += "101010";
      binaryCollection.push_back(binary);
      rd.erase(rd.length()-1);
      rs.erase(rs.length()-1);
      binary = "000000"; //op code
      binary  += m[rt]; //s1: "10001";
      binary  += m[rs]; //s4: "10100";
      binary  += m[at]; //t1: "01001";
      binary  += "00000"; // sa=00000
      binary  += "101010";
      cout << "seq: " << binary << endl;
      binaryCollection.push_back(binary);
    }
    else if(function == "sne"){
      count++;
      infile >> rd >> rs >> rt;
      rd.erase(rd.length()-1);
      rs.erase(rs.length()-1);
      binary = "000000"; //op code
      binary  += m[rs]; //s1: "10001";
      binary  += m[rt]; //s4: "10100";
      binary  += m[at]; //t1: "01001";
      binary  += "00000"; // sa=00000
      binary  += "101010";
      binaryCollection.push_back(binary);
      rd.erase(rd.length()-1);
      rs.erase(rs.length()-1);
      binary = "000000"; //op code
      binary  += m[rt]; //s1: "10001";
      binary  += m[rs]; //s4: "10100";
      binary  += m[at]; //t1: "01001";
      binary  += "00000"; // sa=00000
      binary  += "101010";
      cout << "sne: " << binary << endl;
      binaryCollection.push_back(binary);
    }
    else if(function == "mov"){
      count++;
      infile >> rd >> rs;
      rs.erase(rt.length()-1);
      rd.erase(rd.length()-1);
      binary = "000000";
      binary += "00000";
      binary += m[rs];
      binary += m[rd];
      binary += "00000";
      binary  += "100000"; // add=100000
      cout << "mov: " << binary << endl;
      binaryCollection.push_back(binary);
    }
    else if(function == "li"){
      // ex. li $t0, 5
      // add 5 to at  -> addi $at, $at, 5
      // mov at to li -> mov $t0, $at
      count++;
      infile >> rt >> rs >> immediate;                        // -------
      rt.erase(rt.length()-1);
      rs.erase(rs.length()-1);
      binary = "001000";                                      //ADDI
      binary += m[at]; // rs
      binary += m[at];
      binary += IntegerToString2sComp(stoi(immediate));       // -------
      
      infile >> rd;                                           // -------
      rd.erase(rd.length()-1);
      binary = "000000";
      binary += "00000";
      binary += m[at];                                       //MOV
      binary += m[rd];
      binary += "00000";
      binary  += "100000"; // add=100000                        ---------


      cout << "li: " << binary << endl;
      binaryCollection.push_back(binary);
    }
    else if(function == "bge"){
      count++;
      infile >> rs >> rt;
      rs.erase(rs.length()-1);
      binary = "000000"; //op code
      binary  += m[rs]; //s1: "10001";
      binary  += m[rt]; //s4: "10100";
      binary  += m[at]; //t1: "01001";
      binary  += "00000"; // sa=00000
      binary  += "101010";

      infile >> offset;
      rt.erase(rt.length()-1);
      binary = "000100";
      binary += m[at];
      binary += "00000";
      // cout << m[offset] << " " << offset << endl; 
      binary += IntegerToString2sComp((stoi(m[offset])) - (count+2));

      cout << "bge: " << binary << endl;
      binaryCollection.push_back(binary);
    }
    else if(function == "bgt"){
      count++;
      infile >> rs >> rt;
      rs.erase(rs.length()-1);
      binary = "000000"; //op code
      binary  += m[rs]; //s1: "10001";
      binary  += m[rt]; //s4: "10100";
      binary  += m[at]; //t1: "01001";
      binary  += "00000"; // sa=00000
      binary  += "101010";

      infile >> offset;
      rt.erase(rt.length()-1);
      binary = "000101";
      binary += m[at];
      binary += "00000";
      binary += IntegerToString2sComp((stoi(m[offset])) - (count+2));
      cout << "bgt: " << binary << endl;
      binaryCollection.push_back(binary);
    }
    else if(function == "ble"){
      count++;
      infile >> rs >> rt;
      rs.erase(rs.length()-1);
      binary = "000000"; //op code
      binary  += m[rs]; //s1: "10001";
      binary  += m[rt]; //s4: "10100";
      binary  += m[at]; //t1: "01001";
      binary  += "00000"; // sa=00000
      binary  += "101010";

      infile >> rt >> offset;
      rt.erase(rt.length()-1);
      binary = "000100";
      binary += m[at];
      binary += "00000";
      binary += IntegerToString2sComp((stoi(m[offset])) - (count+2));
      cout << "ble: " << binary << endl;
      binaryCollection.push_back(binary);
    }
    else if(function == "blt"){
      count++;
      infile >> rs >> rt;
      rs.erase(rs.length()-1);
      binary = "000000"; //op code
      binary  += m[rs]; //s1: "10001";
      binary  += m[rt]; //s4: "10100";
      binary  += m[at]; //t1: "01001";
      binary  += "00000"; // sa=00000
      binary  += "101010";

      infile >> offset;
      rt.erase(rt.length()-1);
      binary = "000101";
      binary += m[at];
      binary += "00000";
      binary += IntegerToString2sComp((stoi(m[offset])) - (count+2));
      cout << "blt: " << binary << endl;
      binaryCollection.push_back(binary);
    }
    else if(function == "abs"){
      count++;
      infile >> rs >> rd;
      rs.erase(rt.length()-1);
      binary = "";
      binary += m[rs];
      binary += m[rd];
      cout << "abs: " << binary << endl;
      binaryCollection.push_back(binary);
    }
    else if(function == "or"){
      count++;
      infile >> rs >> rt >> rd;
      rd.erase(rd.length()-1);
      rs.erase(rs.length()-1);
      binary = "000000";
      binary  += m[rs]; //s1: "10001";
      binary  += m[rt]; //s4: "10100";
      binary  += m[rd]; //t1: "01001";
      binary  += "00000"; // sa=00000
      binary  += "100101";// add=100000
      cout << "Or: " << binary << endl;
      binaryCollection.push_back(binary);
    }
    else if(function == "and"){
      count++;
      infile >> rs >> rt >> rd;
      rd.erase(rd.length()-1);
      rs.erase(rs.length()-1);
      binary = "000000";
      binary  += m[rs]; //s1: "10001";
      binary  += m[rt]; //s4: "10100";
      binary  += m[rd]; //t1: "01001";
      binary  += "00000"; // sa=00000
      binary  += "100100";// add=100000
      cout << "and: " << binary << endl;
      binaryCollection.push_back(binary);
    }
    else if(function == "nor"){
      count++;
      infile >> rs >> rt >> rd;
      rd.erase(rd.length()-1);
      rs.erase(rs.length()-1);
      binary = "000000";
      binary  += m[rs]; //s1: "10001";
      binary  += m[rt]; //s4: "10100";
      binary  += m[rd]; //t1: "01001";
      binary  += "00000"; // sa=00000
      binary  += "100111";// add=100000
      cout << "nor: " << binary << endl;
      binaryCollection.push_back(binary);
    }
    else if(function == "xor"){
      count++;
      infile >> rs >> rt >> rd;
      rd.erase(rd.length()-1);
      rs.erase(rs.length()-1);
      binary = "000000";
      binary  += m[rs]; //s1: "10001";
      binary  += m[rt]; //s4: "10100";
      binary  += m[rd]; //t1: "01001";
      binary  += "00000"; // sa=00000
      binary  += "100110";// add=100000
      cout << "xor: " << binary << endl;
      binaryCollection.push_back(binary);
    }
  }
  //this part chunks the strings in the binary collection vector using the string str 
  std::string str2;
  str2 = " ";
  int counter;
  for(string str: binaryCollection){
    for(int i =0; i<str.length();i++){
      counter++;
      if(counter%4 == 0){
          str2 = str2 + str.at(i) + " ";
      }
      else{
          str2 = str2 + str.at(i);
      }
    }
  }
  // This takes the chunked binary text and uses the chunktoHex method to get a vector of strings 
  char charspace = ' ';
  std::vector<std::string> chunkedbin = chunktoHex(str2, charspace);
  // This iterates through the vector of strings and translates it to hex and writes it to the output file
  int counternew = 0;
  outfile << "v3.0 hex words plain" << std::endl;
  for (auto i : chunkedbin){
    if(i == "0000"){
        if(counternew%8==0){
          outfile << "0" << std::endl;
        }
        else{
          outfile << "0";
        }
    }
    else if(i == "0001"){
      if(counternew%8==0){
        outfile << "1" << std::endl;
      }
      else{
        outfile << "1";
      }
    }
    else if(i == "0010"){
      if(counternew%8==0){
        outfile << "2" << std::endl;
      }
      else{
        outfile << "2";
      }
    }
    else if(i == "0011"){
      if(counternew%8==0){
        outfile << "3" << std::endl;
      }
      else{
        outfile << "3";
      }
    }
    else if(i == "0100"){
      if(counternew%8==0){
        outfile << "4" << std::endl;
      }
      else{
        outfile << "4";
      }
    }
    else if(i == "0101"){
      if(counternew%8==0){
        outfile << "5" << std::endl;
      }
      else{
        outfile << "5";
      }
    }
    else if(i == "0110"){
      if(counternew%8==0){
        outfile << "6" << std::endl;
      }
      else{
        outfile << "6";
      }
    }
    else if(i == "0111"){
      if(counternew%8==0){
        outfile << "7" << std::endl;
      }
      else{
        outfile << "7";
      }
    }
    else if(i == "1000"){
      if(counternew%8==0){
        outfile << "8" << std::endl;
      }
      else{
        outfile << "8";
      }
    }
    else if(i == "1001"){
      if(counternew%8==0){
        outfile << "9" << std::endl;
      }
      else{
        outfile << "9";
      }
    }
    else if(i == "1010"){
      if(counternew%8==0){
        outfile << "a" << std::endl;
      }
      else{
        outfile << "a";
      }
    }
    else if(i == "1011"){
      if(counternew%8==0){
        outfile << "b" << std::endl;
      }
      else{
        outfile << "b";
      }
    }
    else if(i == "1100"){
      if(counternew%8==0){
        outfile << "c" << std::endl;
      }
      else{
        outfile << "c";
      }
    }
    else if(i == "1101"){
      if(counternew%8==0){
        outfile << "d" << std::endl;
      }
      else{
        outfile << "d";
      }
    }
    else if(i == "1110"){
      if(counternew%8==0){
        outfile << "e" << std::endl;
      }
      else{
        outfile << "e";
      }
    }
    else if(i == "1111"){
      if(counternew%8==0){
        outfile << "f" << std::endl;
      }
      else{
        outfile << "f";
      }
    }
    counternew++;
  }

  //closes both of our input and output files 
  infile.close();
  outfile.close();

  return 0;
}
