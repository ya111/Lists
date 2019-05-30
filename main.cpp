/* Работа со связанными списками */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/* Описание шаблона структуры list */

struct list
{
    string name;
    string surname;
    string city;
    int inn;
    bool check=0;
    struct list *next_rec;  /* next_rec - указатель на следующую структуру list в связанном списке */
};

/* Определение типов для структуры LIST и указателя LISTPTR на нее */
typedef struct list  LIST;
typedef struct list *LISTPTR;

/* Прототипы функций для работы со списком */
LISTPTR add_to_list(LIST task, LISTPTR first );
void    show_list  (LISTPTR first);
void    check  (LISTPTR first);
void    show_namesakes  (LISTPTR first);
void    show_namesakescity  (LISTPTR first);
void    free_memory_list(LISTPTR first);

int main( void )
{
   LISTPTR first = NULL;  /* указатель на первый элемент списка */
   LIST task;
   int count;

   ifstream file_in("E://input.txt", ios_base:: in );

   if (!file_in) {
       cerr<<"file not found"<<endl;
       return 0;
                 };

   // читаем из file_in

 for (count = 0; !file_in.eof(); count++)
      {
        file_in >> task.name >> task.surname >> task.city >> task.inn;
        first = add_to_list( task, first );
        }

      if (first == NULL)           // выделить память не удалось завершение работы
      {
          cout << "\nUnable to allocate memory!\n" ;
          return 1;
          };
      file_in.close();

    int a;
    while (a!=5)
    {

    cout << "Choose one: \n1) Show all \n2) Add\n3) Show namesakes\n4) Show namesakes from 1 city\n5) Quit\n";
    cin >> a;
    cout <<"\n\n";
   // system("cls");
    if (a==1)
        show_list ( first );           // Вывод всего списка */
   if  (a==2){
       cout << "Input name, surname, city and inn\n";
       cin >> task.name >> task.surname >> task.city >> task.inn;
       first= add_to_list (task,first);
     }
   if (a==3){
       show_namesakes(first);
       }
   if (a==4){
       show_namesakescity(first);
    }
   cout <<"\n\n";
    }
   free_memory_list( first );    // Освобождение памяти, занятой списком */

   return 0;
}

/*========================================================*
 * Function: add_to_list()
 * Purpose : Вставка нового элемента списка
 * Entry   : task
 *           LISTPTR first = указатель на первый элемент списка перед вставкой
 * Returns : Указатель на первый элемент списка после вставки
 *========================================================*/

LISTPTR add_to_list( LIST task, LISTPTR first )
{
   LISTPTR new_rec  = NULL;       /* Указатель на новую запись */
   LISTPTR next_rec = NULL;
   LISTPTR rec      = NULL;


  // new_rec = (LISTPTR)malloc(sizeof(LIST));  /* Выделение памяти для нового элемента списка */
   new_rec = new (LIST);                       /* Выделение памяти для нового элемента списка */

   if (!new_rec) return(NULL);               /* Невозможно выделение памяти - завершение работы */

   /* запись данных нового элемента, но он пока никуда не встроен*/
   new_rec->name = task.name;
   new_rec->surname = task.surname;
   new_rec->city = task.city;
   new_rec->inn = task.inn;
   new_rec->next_rec = NULL;

    if (first == NULL)    /* если список пустой т.е. указатель first=NULL */
   {
       first = new_rec;  /* у него new_rec->next_rec = NULL */
       return(first);
    }

    /* проверка нужно ли поместить новый элемент первым */
    if ( new_rec->inn < first->inn)
      {
         new_rec->next_rec = first;
         first = new_rec;
         return(first);                      // вставили первым - завершение работы функции add_to_list
      }

    // начинаем просматривать все элементы списка

     rec = first;                     // указатель на текущий элемент списка
     next_rec  = rec->next_rec;       // указатель на последующий элемент

     while ( next_rec != NULL )
            {
               if( new_rec->inn < next_rec->inn )   // проверка условия вставки перед элементом next_rec
               {
                  new_rec->next_rec = next_rec;
                  rec->next_rec = new_rec;
                  return(first);                 // вставили- завершение работы функции add_to_list
                }
               else                              // условие вставки перед элементом next_rec не выполнено
               {                                 // переходим к следующему элементу списка
                  rec = next_rec;
                  next_rec  = next_rec->next_rec;
                }
            }

       // пока не достигли конца списка

   rec->next_rec = new_rec;      // достигли конца списка и до сих пор не вышли из функции
                                 // значит вставляем в конец списка (в rec остался указатель на последний),
                                 // а для new_rec->next_rec = NULL см. стр.78;
   return(first);
}

/*========================================================*
 * Function: show_list
 * Вывод всех элементов списка
 *========================================================*/

void show_list( LISTPTR first )
{
   LISTPTR cur_ptr;
   cur_ptr = first;

   while (cur_ptr != NULL )
   {
   cout << cur_ptr->name <<"  " << cur_ptr->surname <<"  " << cur_ptr->city <<"  " << cur_ptr->inn <<  endl ;
   cur_ptr = cur_ptr->next_rec;
   }
}

/*========================================================*
 * Function: free_memory_list
 * Освобождение памяти, занимаемой списком
 *========================================================*/

void free_memory_list(LISTPTR first)
{
   LISTPTR cur_ptr, next_rec;
   cur_ptr = first;

   while (cur_ptr != NULL)          /* перебор всех элементов списка */
   {
      next_rec = cur_ptr->next_rec; /* указатель на следующий элемент списка */
 //     free(cur_ptr); // используется, если для выделения памяти применялся malloc
      delete(cur_ptr);
      cur_ptr = next_rec;
   }
}

void show_namesakes( LISTPTR first )
{
   LISTPTR cur_ptr, cur_ptr2;
   cur_ptr = first;
   cur_ptr2=cur_ptr->next_rec;
   int s=0,n=0;
   while (cur_ptr != NULL )
   {
      // ptr3=cur_ptr2;
       while (cur_ptr2 != NULL)
       {
           if (cur_ptr->surname == cur_ptr2->surname)
           {
               if (cur_ptr->check == 0 ){
                   n++;
                   cout << "\n" << n <<" surname: \n";
                   s++;
                   cout << s << " human: " <<cur_ptr->name <<"  " << cur_ptr->surname <<"  " << cur_ptr->city <<"  " << cur_ptr->inn <<  endl ;

               }
               if (cur_ptr2->check == 0){
                   s++;
                   cout << s << " human: " <<cur_ptr2->name <<"  " << cur_ptr2->surname <<"  " << cur_ptr2->city <<"  " << cur_ptr2->inn <<  endl ;
               }
               cur_ptr->check = 1;
               cur_ptr2->check = 1;
           }
           cur_ptr2 = cur_ptr2->next_rec;
       }
      cur_ptr = cur_ptr->next_rec;
      if (cur_ptr!= NULL)
          cur_ptr2=cur_ptr->next_rec;
   }
   check(first);
   if (s==0) cout << "Didn't find namesakes" << endl;
}

void show_namesakescity( LISTPTR first )
{
   LISTPTR cur_ptr, cur_ptr2;
   cur_ptr = first;
   cur_ptr2=cur_ptr->next_rec;
   int s=0, t=0, n=0;
   while (cur_ptr != NULL )
   {
      // ptr3=cur_ptr2;
       while (cur_ptr2 != NULL)
       {
           if ((cur_ptr->surname == cur_ptr2->surname) && (cur_ptr->city == cur_ptr2->city))
           {
              // if (s==1)

               if (cur_ptr->check == 0 ){
                   n++;
                   cout << "\n" << n <<" surname+city: \n";
                   s++;
                   cout << s << " human: " <<cur_ptr->name <<"  " << cur_ptr->surname <<"  " << cur_ptr->city <<"  " << cur_ptr->inn <<  endl ;

               }
               if (cur_ptr2->check == 0){
                   s++;
                   cout << s << " human: " <<cur_ptr2->name <<"  " << cur_ptr2->surname <<"  " << cur_ptr2->city <<"  " << cur_ptr2->inn <<  endl ;
               }
               cur_ptr->check = 1;
               cur_ptr2->check = 1;
           }
          // cout << cur_ptr2 << " cur_ptr2\n";
           cur_ptr2 = cur_ptr2->next_rec;
       }
      cur_ptr = cur_ptr->next_rec;

      //cout << cur_ptr << " cur_ptr\n";
      if (cur_ptr!= NULL)
          cur_ptr2=cur_ptr->next_rec;
   }
   check (first);
   if (s==0) cout << "Didn't find namesakes from 1 city" << endl;
}

void check (LISTPTR first)
{
    LISTPTR cur_ptr;
    cur_ptr = first;
    while (cur_ptr != NULL ){
        cur_ptr->check=0;
        cur_ptr = cur_ptr->next_rec;
    }
}
