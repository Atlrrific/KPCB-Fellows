#include <iostream>

#include <functional>
#include <string>



using namespace std;

template<class T >

//Hash entry class that stores the key and value of the entries
class HashEntry {
private:

      string key;
      T * value;
public:
      HashEntry(string key, T * value) {
            this->key = key;
            this->value = value;
      }
 
      string getKey() {
            return key;
      }
  
      T  * getValue() {
            return value;
      }
};



template<class TYPE >
class HashTable{
  private:
    HashEntry < TYPE > ** table;
    int size;
    int numOfItems;
    hash<string> hash_fn;
    
  public:

    //HASHTABLE constructor
    HashTable(int size){
      this->size  = size;
      this->table = new HashEntry <TYPE > *[size];
      this->numOfItems = 0;
      for (int i = 0; i < size; i++)
                  table[i] = NULL;
    }
  
    //HashTable set method
    bool set (string key, TYPE * val){

      //Return if the Table is Full
      if(load() == 1){
        return false;
      }

      HashEntry <TYPE > * newEntry = new HashEntry <TYPE > (key,val);
      u_int str_hash = hash_fn(key);
      u_int index = str_hash%size;

      //Iterate in case of collision moving to the next index
      while(table[index]!=NULL && table[index]->getKey()!=key){
        /*We have looped thorugh all the table*/
        printf("Inside Loop\n" );

        str_hash+=1;
        index = str_hash%size;
        // count++;
      }
      table[index] = newEntry;

      this->numOfItems++;
      return true;
    }
  
    //Hashtable Get Method
    TYPE * get(string key){
      u_int str_hash = hash_fn(key);
      u_int index = str_hash%size;
      int count  = 0;
      printf("------------------------\n" );
      printf("GET: %u\n", index );


      while(table[index]!=NULL && table[index]->getKey()!=key){
            //Item not found after all iterations
            if(count  == (size-1)){
              return NULL;
            }
            str_hash+=1;
            index = str_hash%size;
            count++;
      }
      if(table[index]== NULL){
        return NULL;
      }else{

        return table[index]->getValue();
      }

    }

    //Delete Key Method 
    //TODO fix Bug
    TYPE * deleteKey(string key){
      u_int str_hash = hash_fn(key);
      u_int index = str_hash%size;
      int count  = 0;
      printf("Le Index %d\n", index );

      //TYPE * valueRemoved;
        //Iterate thorugh the table until 
     // if(table[index]==NULL ){
     //    printf("Is gonna enter loop\n");
     //  }else{
     //    printf("Is NOT gonna enter loop\n");
     //  }
      while(table[index]!=NULL ){
        printf("Le Loop Index %d\n", index );
        if(table[index]->getKey()==key){
          break;
        }
          printf("Le Loop Index %d\n", index );
            //Item not found after all iterations
            if(count  == (size-1)){
              return NULL;
            }
            str_hash+=1;
            index = str_hash%size;
            count++;

            printf("Le Index %d\n", index );
        
      }

      if(table[index] == NULL ){
        return NULL;
        
      }else{

        //Removing value found
        TYPE * valueRemoved = table[index]->getValue();
        table[index] =  NULL;

        //Check if there is a next element in the array
        str_hash+=1;
        index = str_hash%size;
        while(table[index]!=NULL){
          //Swap the next item on the table
          TYPE * value = table[index]->getValue();
          string key = table[index]->getKey();
          // printf("Le key removed%s\n",  key);
          table[index] = NULL;
          set(key,value);
          
          //Update the index
          str_hash+=1;
          index = str_hash%size;
        }

        this->numOfItems--;
        return valueRemoved;
      
      }
      
    }

    float load(){
      float loadVal = (float)numOfItems/size;
      return loadVal;
    }
    
};

int main() {

  HashTable <int > * table = new HashTable<int>(5);

  //On the main I tested insertion and seach, 
  //Also delete was tested but need some fixes beacuse of bugs
  int y = 16;
  bool insertVal = table->set("a", &y);
  printf("Insert 1: %d\n", insertVal);
  
  int * res = table->get("a");

  printf("Search 1: Expected : %d Result : %d\n", 16,*res);

  int x = 1;
  insertVal = table->set("b", &x);
  printf("Insert 1: %d\n", insertVal);

  printf("%f\n", table->load() );

  res = table->get("b");

  printf("Search 2: Expected : %d Result : %d\n", 1,*res);


   int p = 10;
   insertVal = table->set("c", &p);
  printf("Insert 1: %d\n", insertVal);

  printf("%f\n", table->load() );

  res = table->get("c");

  printf("Search 2: Expected : %d Result : %d\n", 10,*res);


   int m = 90;
   insertVal = table->set("d", &m);
  printf("Insert 1: %d\n", insertVal);

  printf("%f\n", table->load() );

  res = table->get("d");

  printf("Search 2: Expected : %d Result : %d\n", 90,*res);


  int n = 92;
  insertVal = table->set("e", &n);
  printf("Insert 1: %d\n", insertVal);

  printf("%f\n", table->load() );

  res = table->get("e");

  printf("Search 2: Expected : %d Result : %d\n", 92,*res);

  int l = 100;
  insertVal = table->set("h", &l);
  printf("Insert 1: %d\n", insertVal);

  printf("%f\n", table->load() );

  res = table->get("h");
  if(res == NULL){
    printf("Test Passed\n");
  }

  /////These test did not work successfully need more work to debug//
  //Progress will be on the github repo
  printf("Deleteing 1 a\n");
  int * del = table->deleteKey("a");
  if(del == NULL){
    printf("Does not work null :S\n");
  }else{
    printf("Delete 1    :   %d\n", *del);
  }
  
  printf("Searhing for a\n");
  int * search = table->get("a");

  if(search == NULL){
    printf("ITS NULL on the search\n");
  }else{
    printf("Search 2%d\n", *search);
  }
  printf("Le Load%f\n", table->load() );
  // 


printf("---------------------------\n");

   search = table->get("b");

  if(search == NULL){
    printf("ITS NULL on the search\n");
  }else{
    printf("Search 2%d\n", *search);
  }
printf("---------------------------\n");


  printf("Deleteing 2 on B\n");
   del = table->deleteKey("b");
  if(del == NULL){
    printf("Does not work null :S\n");
  }else{
    printf("Delete 2    :   %d\n", *del);
  }


   search = table->get("b");

  if(search == NULL){
    printf("ITS NULL on the search\n");
  }else{
    printf("Search 2%d\n", *search);
  }


printf("---------------------------\n");

printf("Searching for d\n");
search = table->get("d");

  if(search == NULL){
    printf("ITS NULL on the search BAD\n");
  }else{
    printf("Finding d: %d\n", *search);
  }



printf("---------------------------\n");


    printf("Deleteing 2 on D\n");
   del = table->deleteKey("d");
  if(del == NULL){
    printf("Does not work null :S\n");
  }else{
    printf("Delete 2    :   %d\n", *del);
  }

   search = table->get("d");

  if(search == NULL){
    printf("ITS NULL on the search");
  }else{
    printf("Search 2%d\n", *search);
  }


printf("---------------------------\n");


    printf("Deleteing 2 on D for the second time\n");
   del = table->deleteKey("d");
  if(del == NULL){
    printf("Works\n");
  }else{
    printf("Delete 2    :   %d\n", *del);
  }

   search = table->get("d");

  if(search == NULL){
    printf("ITS NULL on the search");
  }else{
    printf("Search 2%d\n", *search);
  }

  return 0;
}
