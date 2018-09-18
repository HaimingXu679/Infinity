#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <stdio.h>
#include <iomanip>
#include <set>
#include <utility>
#include <cmath>
using namespace std;

char numbers[11]={'0','1','2','3','4','5','6','7','8','9','.'};
vector<int> number1,number2,answer,danswer,num1dec,num2dec;
bool mq=0,eq=0,decimal_1=0,decimal_2=0,negative=0,zero=0,combinatorics=0,division=0;
ifstream infile;
ofstream outfile;

class v2{
public:
  vector<int> v;
};

vector<pair<v2,v2> > database;

typedef v2 v2_type;

void print1(){
  for (int i=0;i<number1.size();i++) cout << number1[i];
  cout << endl;
  return;
}

void print2(){
  for (int i=0;i<number2.size();i++) cout << number2[i];
  cout << endl;
  return;
}

void clearAll(){
  number1.clear();
  number2.clear();
  return;
}

int bigger(){
  //0 means 1 is bigger, 1 means equal, 2 means 2 is bigger
  if (number1.size()>number2.size()) return 0;
  else if (number1.size()==number2.size()){
    for (int i=0;i<number1.size();i++){
      if (number1[i]>number2[i]) return 0;
      else if (number1[i]<number2[i]) return 2;
    }
    return 1;
  }
  return 2;
}

void sum(){
  answer.clear();
  int i,j;
  for (i=0;i<number1.size();i++) if (number1[i]!=0) break;
  if (i==number1.size()){
    number1.clear();
    number1.push_back(0);
  }
  for (i=0;i<number2.size();i++) if (number2[i]!=0) break;
  if (i==number2.size()){
    number2.clear();
    number2.push_back(0);
  }
  //aligning the two numbers to set up addition
  if (number1.size()>=number2.size()){
    int index=number1.size()-1;
    for (i=number2.size()-1;i>=0;i--){
      answer.push_back(number1[index]+number2[i]);
      index--;
    }
    for (i=number1.size()-1-number2.size();i>=0;i--)
      answer.push_back(number1[i]);
  }
  else{
    int index=number2.size()-1;
    for (i=number1.size()-1;i>=0;i--){
      answer.push_back(number1[i]+number2[index]);
      index--;
    }
    for (i=number2.size()-1-number1.size();i>=0;i--)
      answer.push_back(number2[i]);
  }
  //finds out if there is any carry, then adjusts
  while (1){
    bool breaker=0;
    for (i=0;i<answer.size()-1;i++){
      if (answer[i]>9){
        answer[i+1]++;
        answer[i]-=10;
        breaker=1;
      }
    }
    if (!breaker) break;
  }
  if (answer[answer.size()-1]>9){
    answer[answer.size()-1]-=10;
    answer.push_back(1);
  }
  //reverses the answer since it's backwards
  for (i=0;i<answer.size()/2;i++) swap(answer[i],answer[answer.size()-1-i]);
  danswer.clear();
  //adds decimals
  if (num1dec.size()!=0){
    if (num1dec.size()>=num2dec.size()){
      int index=num1dec.size()-1;
      for (i=num2dec.size()-1;i>=0;i--){
        danswer.push_back(num1dec[index]+num2dec[i]);
        index--;
      }
      for (i=num1dec.size()-1-num2dec.size();i>=0;i--)
        danswer.push_back(num1dec[i]);
    }
    else{ 
      int index=num2dec.size()-1;
      for (i=num1dec.size()-1;i>=0;i--){
        danswer.push_back(num1dec[i]+num2dec[index]);
        index--;
      }
      for (i=num2dec.size()-1-num1dec.size();i>=0;i--)
        danswer.push_back(number2[i]);
    }
    //adjusts carry for decimals
    while (1){
      bool breaker=0;
      for (i=0;i<danswer.size()-1;i++){
        if (danswer[i]>9){
          danswer[i+1]++;
          danswer[i]-=10;
          breaker=1;
        }
      }
      if (!breaker) break;
    }
    if (danswer[danswer.size()-1]>9){
      danswer[danswer.size()-1]-=10;
      danswer.push_back(1);
    }
    for (i=0;i<danswer.size()/2;i++) swap(danswer[i],danswer[danswer.size()-1-i]);
    if (danswer.size()>num1dec.size()){
      danswer.erase(danswer.begin());
      answer[answer.size()-1]++;
      while (1){
        bool breaker=0;
        for (i=0;i<answer.size()-1;i++){
          if (answer[i]>9){
            answer[i+1]++;
            answer[i]-=10;
            breaker=1;
          }
        }
        if (!breaker) break;
      }
      if (answer[answer.size()-1]>9){
        answer[answer.size()-1]-=10;
        answer.push_back(1);
      }
    }
  }
  //prints out the number
  if (!mq && !division){
    for (i=0;i<answer.size();i++) outfile << answer[i];
    if (danswer.size()>0){ 
      if (num1dec.size()!=0) outfile << ".";
      for (i=0;i<danswer.size();i++) outfile << danswer[i];
    }
    if (danswer.size()==1 && danswer[0]==0)
      outfile << endl << "Your answer has " << answer.size() << " digit(s)." << endl;
    else outfile << endl << "Your answer has " << answer.size()+danswer.size() 
                 << " digit(s)." << endl;
  }
}

void subtract(){
  int i,j;
  answer.clear();
  for (i=0;i<number1.size();i++) if (number1[i]!=0) break;
  if (i==number1.size()){
    number1.clear();
    number1.push_back(0);
  }
  for (i=0;i<number2.size();i++) if (number2[i]!=0) break;
  if (i==number2.size()){
    number2.clear();
    number2.push_back(0);
  }
  //finds which number is bigger
  if (bigger()==1){
    answer.clear();
    negative=0;
    answer.push_back(0);
    if (!division) outfile << 0 << endl;
    return;
  }
  if (bigger()==2){
    int temp=number1.size(),temp2=number2.size(); 
    for (i=0;i<number2.size();i++) number1.push_back(number2[i]);
    for (i=0;i<temp;i++) number2.push_back(number1[i]);
    number1.erase(number1.begin(),number1.begin()+temp);
    number2.erase(number2.begin(),number2.begin()+temp2);
    negative=1;
  }
  else negative=0;
  vector<int>::iterator it;
  while(number1.size()!=number2.size()){
    it=number2.begin();
    number2.insert(it,0);
  }
  for (i=number1.size()-1;i>=0;i--){
    if (number1[i]<number2[i]){
      number1[i]+=10;
      number1[i-1]-=1;
    }
    answer.push_back(number1[i]-number2[i]);
  }
  for (i=0;i<answer.size()/2;i++) swap(answer[i],answer[answer.size()-1-i]);
  for (i=0;i<answer.size();i++) if (answer[i]!=0) break;
  answer.erase(answer.begin(),answer.begin()+i);
  if (!division){
    if (negative) outfile << "-";
    for (i=0;i<answer.size();i++) outfile << answer[i];
    outfile << endl;
  }
}

void multiply(){
  int i,j,counter=0;
  for (i=0;i<number1.size();i++) if (number1[i]!=0) break;
  if (i==number1.size()){
    number1.clear();
    number1.push_back(0);
  }
  for (i=0;i<number2.size();i++) if (number2[i]!=0) break;
  if (i==number2.size()){
    number2.clear();
    number2.push_back(0);
  }
  mq=1;
  vector<v2> a;
  answer.clear();
  for (i=number2.size()-1;i>=0;i--){
    v2 temp;
    a.push_back(temp);
    for (j=number1.size()-1;j>=0;j--)
      a[counter].v.push_back(number1[j]*number2[i]); 
    while (1){
      bool breaker=0;
      for (j=0;j<a[counter].v.size()-1;j++){
        if (a[counter].v[j]>9){
          a[counter].v[j+1]+=(a[counter].v[j]/10);
          a[counter].v[j]=a[counter].v[j]%10;
          breaker=1;
        }
      }
      if (!breaker) break;
    }
    if (a[counter].v[a[counter].v.size()-1]>9){
      int ph=a[counter].v[a[counter].v.size()-1];
      a[counter].v[a[counter].v.size()-1]=(ph%10);
      a[counter].v.push_back(ph/10);
    }
    for (j=0;j<a[counter].v.size()/2;j++) 
      swap(a[counter].v[j],a[counter].v[a[counter].v.size()-1-j]);
    for (j=0;j<counter;j++) a[counter].v.push_back(0);
    counter++;
  }
  number1.clear();
  number2.clear();
  for (j=0;j<a[0].v.size();j++) number2.push_back(a[0].v[j]);
  for (i=1;i<counter;i++){
    for (j=0;j<a[i].v.size();j++) number1.push_back(a[i].v[j]);
    sum();
    number1.clear();
    number2.clear(); 
    for (j=0;j<answer.size();j++) number2.push_back(answer[j]);
  }
  if (!eq && !division) for (i=0;i<answer.size();i++) outfile << answer[i];
  if (counter<2){
    if (eq==0 && !division) for (i=0;i<number2.size();i++) outfile << number2[i];
    for (i=0;i<number2.size();i++) answer.push_back(number2[i]);
  }
  if (!eq && !division)
    outfile << endl << "Your answer has " << answer.size() << " digits." << endl;
}


/*void divide(){
  vector<v2> patterns;
  division=1;
  int i,j,position=0,used=0,points=0,zc=0,repeats=0,newpos,
      num1osize=number1.size()+num1dec.size();
  for (i=0;i<number1.size();i++) if (number1[i]!=0) break;
  number1.erase(number1.begin(),number1.begin()+i);
  for (i=0;i<number2.size();i++) if (number2[i]!=0) break;
  number2.erase(number2.begin(),number2.begin()+i);
  for (i=0;i<number1.size();i++) if (number1[i]!=0) break;
  if (i==number1.size()){
    outfile << 0 << endl;
    return;
  }
  if (number2.size()==0){
    if (num2dec.size()==0){
      outfile << "DNE" << endl;
      return;
    }
    for (i=0;i<num2dec.size();i++) if (num2dec[i]!=0) break;
    if (i==num2dec.size()){
      outfile << "DNE" << endl;
      return;
    }
  }
  if (number2[0]==1 && number2.size()==1){
    answer.clear();
    for (i=0;i<number1.size();i++) answer.push_back(number1[i]);
    for (i=0;i<answer.size();i++) outfile << answer[i];
    outfile << endl;
    return;
  }
  if (number2[0]==1 && number2.size()>1){
    for (i=1;i<number2.size();i++){
      if (number2[i]!=0) break;
      zc++;
    }
    if (i==number2.size()){
      if (zc>number1.size()){
        outfile << "."; 
        for (j=0;j<zc-number1.size();j++) outfile << 0;
        for (j=0;j<number1.size();j++) outfile << number1[j];
        outfile << endl;
      }
      else{
        for (j=0;j<number1.size()-zc;j++) outfile << number1[j];
        for (j=number1.size()-zc;j<number1.size();j++) if (number1[j]!=0) break;
        if (j!=number1.size()){
          outfile << ".";
          for (j=number1.size()-zc;j<number1.size();j++) outfile << number1[j];
        }
        outfile << endl;
      }
      return; 
    }
  }
  bool breaker=0,zeroes=0;
  vector<int> divideAnswer,onum1,onum2,copy;
  for (i=0;i<number1.size();i++) onum1.push_back(number1[i]);
  for (i=0;i<number2.size();i++) onum2.push_back(number2[i]);
  for (i=0;i<num1dec.size();i++) onum1.push_back(num1dec[i]);
  for (i=0;i<num2dec.size();i++) onum2.push_back(num2dec[i]);
  while(1){
    vector<int> copy;
    int position=0;
    while(1){
      if (repeats!=0) break;
      clearAll();
      for (i=0;i<onum2.size();i++) number2.push_back(onum2[i]);
      if (position<onum1.size()) copy.push_back(onum1[position]);
      else{
        copy.push_back(0);
        onum1.push_back(0);
      }
      for (i=0;i<copy.size();i++) number1.push_back(copy[i]);
      subtract();
      if (repeats==0 && !negative) break;
      position++;
    }
    if (repeats!=0){
      for (i=0;i<newpos;i++) copy.push_back(onum1[i]);
      position=newpos;
    }
    for (i=0;i<10;i++){
      clearAll();
      for (j=0;j<onum2.size();j++) number1.push_back(onum2[j]);
      number2.push_back(i);
      multiply();
      clearAll();
      for (j=0;j<copy.size();j++) number1.push_back(copy[j]);
      for (j=0;j<answer.size();j++) number2.push_back(answer[j]);
      if (bigger()==2) break;
    }
    divideAnswer.push_back(i-1);
    clearAll();
    for (j=0;j<onum2.size();j++) number1.push_back(onum2[j]);
    number2.push_back(i-1);
    multiply();
    clearAll();
    for (i=0;i<copy.size();i++) number1.push_back(copy[i]);
    for (i=0;i<answer.size();i++) number2.push_back(answer[i]);
    subtract();
    for (i=0;i<answer.size();i++) if (answer[i]!=0) break;
    answer.erase(answer.begin(),answer.begin()+i);
    if (repeats==0) onum1.erase(onum1.begin(),onum1.begin()+position+1);
    else onum1.erase(onum1.begin(),onum1.begin()+position);
    vector<int>::iterator it=onum1.begin();
    for (i=0;i<answer.size();i++){
      onum1.insert(it,answer[i]);
      it++;
    }
    if (repeats==0) used=position+1;
    else used++;
    newpos=answer.size()+1;
    if (onum1.size()==0 && used>=num1osize) break;
    if (zeroes) onum1.push_back(0);
    for (i=0;i<onum1.size();i++) if (onum1[i]!=0) break;
    if (zeroes==0 && used>=num1osize){
      zeroes=1;
      points--;
      onum1.push_back(0);
    }
    if (repeats==60 && zeroes){
      points++;
      break;
    }
    if (zeroes){
      repeats++;
      points--;
    }
    else repeats=1;
  }
  points+=(num2dec.size()-num1dec.size());
  while (1){
    if (points>=0) break;
    if (divideAnswer[divideAnswer.size()-1]==0){
      divideAnswer.erase(divideAnswer.begin()+divideAnswer.size()-1);
      points++;
    }
    else break;
  }
  if (points<0){
    points=-points;
    if (points>divideAnswer.size()){
      for (i=0;i<points-divideAnswer.size();i++) outfile << 0;
      outfile << ".";
      for (i=0;i<divideAnswer.size();i++) outfile << divideAnswer[i];
      outfile << endl;
    }
    else{
      for (i=0;i<divideAnswer.size()-points;i++) outfile << divideAnswer[i];
      outfile << ".";
      for (i=divideAnswer.size()-points;i<divideAnswer.size();i++)
        outfile << divideAnswer[i];
      outfile << endl;
    }
  }
  else{
    if (!combinatorics){
      for (i=0;i<divideAnswer.size();i++) outfile << divideAnswer[i];
      for (i=0;i<points;i++) outfile << 0;
      outfile << endl;
    }
  }
  answer.clear();
  for (i=0;i<divideAnswer.size();i++) answer.push_back(divideAnswer[i]); 
  return;
}*/

void divide(){
  int i;
  double a,b,c;
  a=b=c=0;
  for (i=0;i<number1.size();i++){
    a*=10;
    a+=number1[i];
  }
  for (i=0;i<number2.size();i++){
    b*=10;
    b+=number2[i];
  }
  c=a/b;
  outfile << c << endl;
}

void raise(){
  int i,j,number=0;
  eq=1;
  for (i=0;i<number2.size();i++){
    number+=number2[i];
    number*=10;
  }
  number/=10;
  number2.clear();
  vector<int> original;
  for (i=0;i<number1.size();i++){
    number2.push_back(number1[i]);
    original.push_back(number1[i]);
  }
  for (i=0;i<number-1;i++){
    multiply();
    number1.clear();
    number2.clear();
    for (j=0;j<answer.size();j++) number1.push_back(answer[j]); 
    for (j=0;j<original.size();j++) number2.push_back(original[j]); 
  }
  if (!combinatorics){
    for (i=0;i<answer.size();i++) outfile << answer[i];
    outfile << endl << "Your answer has " << answer.size() << " digits." << endl;
  }
}

void factorial(){
  int i,j,number=0,data_used=0,biggest=0;
  infile.close();
  infile.open("database.in");
  v2 input_temp3;
  vector<long long> used;
  while (!infile.eof()){
    string input_temp;
    v2 input_temp4;
    input_temp3.v.clear();
    infile >> input_temp;
    for (j=0;j<input_temp.size();j++) input_temp4.v.push_back(input_temp[j]-48);
    long long input_intform;
    for (i=0;i<input_temp4.v.size();i++){
      input_intform+=input_temp4.v[i];
      input_intform*=10;
    }
    for (i=0;i<used.size();i++) if (used[i]==input_intform) break;
    if (i==used.size()){
      infile >> input_temp;
      for (j=0;j<input_temp.size();j++) input_temp3.v.push_back(input_temp[j]-48);
      database.push_back(make_pair(input_temp4,input_temp3));
    }
    else infile >> input_temp;
    used.push_back(input_intform);
  }
  input_temp3.v.clear();
  input_temp3.v.push_back(1);
  database.push_back(make_pair(input_temp3,input_temp3));
  infile.close();
  eq=1;
  for (i=0;i<number1.size();i++){
    number+=number1[i];
    number*=10;
  }
  number/=10; 
  if (number==0){
    outfile << 1 << endl;
    return;
  }
  if (number<0){
    outfile << "Undefined" << endl;
    return;
  }
  number2.clear();
  for (j=0;j<database.size();j++){
    int endpoint=0;
    for (i=0;i<database[j].first.v.size();i++){
      endpoint+=database[j].first.v[i];
      endpoint*=10;
    }
    endpoint/=10;
    if (endpoint<=number){
      if (endpoint>biggest){
        biggest=endpoint;
        data_used=j;
      }
    }
  }
  clearAll();
  for (i=0;i<database[data_used].second.v.size();i++) 
    number1.push_back(database[data_used].second.v[i]);
  if (biggest!=number){
    for (i=biggest+1;i<=number;i++){
      int temp=i;
      number2.clear();
      while(temp>0){
        number2.push_back(temp%10);
        temp/=10;
      }
      for (j=0;j<number2.size()/2;j++) 
        swap(number2[j],number2[number2.size()-1-j]);
      multiply();
      number1.clear();
      for (j=0;j<answer.size();j++) number1.push_back(answer[j]);
    }
  }
  else{
    answer.clear();
    for (i=0;i<number1.size();i++) answer.push_back(number1[i]);
  }
  if (!combinatorics){
    for (j=0;j<answer.size();j++) outfile << answer[j];
    outfile << endl << "Your answer has " << answer.size() << " digits." << endl;
    outfile.close();
    outfile.open("database.in",fstream::app);
    outfile << number << " ";
    for (j=0;j<answer.size();j++) outfile << answer[j];
    outfile << endl;
  }
}

void log(){
  double number=0,base=0;
  int i;
  for (i=0;i<number2.size();i++){
    number+=number2[i];
    number*=10;
  }
  number/=10;
  for (i=0;i<number1.size();i++){
    base+=number1[i];
    base*=10;
  }
  base/=10;
  outfile << setprecision(10000) << log(number)/log(base) << endl;
}

void combo(){
  int i;
  combinatorics=division=1;
  vector<int> n1c,n2c,numerator,d1,d2;
  for (i=0;i<number2.size();i++) n2c.push_back(number2[i]);
  for (i=0;i<number1.size();i++) n1c.push_back(number1[i]);
  factorial();
  for (i=0;i<answer.size();i++) numerator.push_back(answer[i]);
  answer.clear();
  number1.clear();
  number2.clear();
  for (i=0;i<n2c.size();i++) number1.push_back(n2c[i]);
  factorial();
  for (i=0;i<answer.size();i++) d1.push_back(answer[i]);
  number1.clear();
  number2.clear();
  for (i=0;i<n1c.size();i++) number1.push_back(n1c[i]);
  for (i=0;i<n2c.size();i++) number2.push_back(n2c[i]);
  subtract();
  number1.clear();
  number2.clear();
  for (i=0;i<answer.size();i++) number1.push_back(answer[i]);
  factorial();
  for (i=0;i<answer.size();i++) d2.push_back(answer[i]);
  number1.clear();
  number2.clear();
  for (i=0;i<numerator.size();i++) number1.push_back(numerator[i]);
  for (i=0;i<d1.size();i++) number2.push_back(d1[i]);
  divide();
  number1.clear();
  number2.clear();
  for (i=0;i<answer.size();i++) number1.push_back(answer[i]);
  for (i=0;i<d2.size();i++) number2.push_back(d2[i]);
  divide();
  for (i=0;i<answer.size();i++) outfile << answer[i];
  outfile << endl << "Your answer has " << answer.size() << " digits." << endl;
}

void permu(){
  int i;
  combinatorics=division=1;
  vector<int> n1c,n2c,numerator,d1;
  for (i=0;i<number2.size();i++) n2c.push_back(number2[i]);
  for (i=0;i<number1.size();i++) n1c.push_back(number1[i]);
  factorial();
  for (i=0;i<answer.size();i++) numerator.push_back(answer[i]);
  answer.clear();
  number1.clear();
  number2.clear();
  for (i=0;i<n1c.size();i++) number1.push_back(n1c[i]);
  for (i=0;i<n2c.size();i++) number2.push_back(n2c[i]);
  subtract();
  number1.clear();
  number2.clear();
  for (i=0;i<answer.size();i++) number1.push_back(answer[i]);
  factorial();
  for (i=0;i<answer.size();i++) d1.push_back(answer[i]);
  number1.clear();
  number2.clear();
  for (i=0;i<numerator.size();i++) number1.push_back(numerator[i]);
  for (i=0;i<d1.size();i++) number2.push_back(d1[i]);
  divide();
  for (i=0;i<answer.size();i++) outfile << answer[i];
  outfile << endl << "Your answer has " << answer.size() << " digits." << endl;
}

void root(){
  
}

void sin(){
  int i;
  long long pidecimals=2831853072;
  for (i=0;i<number1.size();i++) cout << number1[i];
  cout << ".";
  for (i=0;i<num1dec.size();i++) cout << num1dec[i];
  cout << endl;
  number2.push_back(6);
  while(pidecimals>0){
    num2dec.push_back(pidecimals%10);
    pidecimals/=10;
  }
  subtract();
  for (i=0;i<answer.size();i++) cout << answer[i];
  cout << endl;
}

int main(){
  int i,j,n,tcounter=0;
  infile.open("inf.in");
  outfile.open("inf.txt");
  char temp,op,op2='n';
  bool first=1,second=1;
  while (1){
    infile >> temp;
    for (i=0;i<11;i++) if (temp==numbers[i]) break; 
    if (infile.eof()) break; 
    if (i!=11){
      if (first){
        if (i!=10){
          if (!decimal_1) number1.push_back(i);
          else num1dec.push_back(i);
        }
        else decimal_1=1;
      }
      if (!first){
        if (i!=10){
          if (!decimal_2) number2.push_back(i);
          else num2dec.push_back(i);
        }
        else decimal_2=1;
      }
    }
    else{
      first=0; 
      op=temp;
      tcounter=-1;
    }
    if (op=='!' || op=='S' || op=='s') break;
    tcounter++;
  }
  if (op!='/'){
    if (num1dec.size()<num2dec.size())
      while (num1dec.size()!=num2dec.size()) num1dec.push_back(0);
    else if (num1dec.size()>num2dec.size())
      while (num1dec.size()!=num2dec.size()) num2dec.push_back(0);
  }
  for (i=0;i<number1.size();i++) outfile << number1[i]; 
  if (decimal_1){
    outfile << ".";
    for (i=0;i<num1dec.size();i++) outfile << num1dec[i];
  }
  outfile << " " << op << " ";
  for (i=0;i<number2.size();i++) outfile << number2[i];
  if (decimal_2){
    outfile << ".";
    for (i=0;i<num2dec.size();i++) outfile << num2dec[i];
  }
  outfile << " = " << endl;
  if (op=='+') sum();
  else if (op=='-') subtract();
  else if (op=='*') multiply();
  else if (op=='/') divide();
  else if (op=='^') raise();
  else if (op=='!') factorial();
  else if (op=='l') log();
  else if (op=='C') combo();
  else if (op=='P') permu();
  else if (op=='S') root();
  else if (op=='s') sin();
  else outfile << "You did not enter a valid operation." << endl;
  return 0;
}
