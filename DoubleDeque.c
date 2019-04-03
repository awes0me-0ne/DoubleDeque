#include<stdio.h>
#include<stdlib.h>//malloc用
#define NODATA 0//データ無し
#define EXISTDATA 1//データあり

/*
int型データを保持するセル
デクで用いる
自己参照構造体
 */
struct doubleCell{
  double data;             //データ部
  struct doubleCell * prev;//前へのポインタ部
  struct doubleCell * next;//後ろへのポインタ部
};

typedef struct doubleCell DoubleCell ;
typedef DoubleCell* Cell_P; //セル型

struct doubleDeque{
  DoubleCell * head;//先頭ポインタ
  DoubleCell * tail;//末尾ポインタ
};

typedef struct doubleDeque DoubleDeque;//デク型

DoubleDeque makeDeque();//デクの作成

void head_in(DoubleDeque *deque,double data);//先頭からデータ挿入
double head_out(DoubleDeque *deque);//先頭からデータ削除
void tail_in(DoubleDeque *deque,double data);//末尾からデータ挿入
double tail_out(DoubleDeque *deque);//末尾からデータ削除

double isEmpty(DoubleDeque *deque);//空のテスト
void printDeque(DoubleDeque *deque);//デク表示
void copyDeque(DoubleDeque *deque1,DoubleDeque *deque2);//デク１をデク２に複製

void fscanToDeque(FILE*fp,DoubleDeque *deque);//ファイルからのデータ入力
void forward_fprint(FILE*fp,DoubleDeque *deque);//ファイルへ順方向に出力
void reverse_fprint(FILE*fp,DoubleDeque *deque);//ファイルへ逆方向に出力

Cell_P makeCell(double n);//セル作成

int main(){
  //デクの動作
  DoubleDeque deque1,deque2;
  DoubleDeque *d_p1,*d_p2;
  FILE *fp_in,*fp_out;

  deque1=makeDeque();//デク１の生成
  d_p1=&deque1;
  deque2=makeDeque();//デク２の生成
  d_p2=&deque2;

  printf("デク用意\n");
  printf("デク１を表示します、\n");
  printDeque(d_p1);
  printf("デク２を表示します。");
  printDeque(d_p2);
  
  fp_in=fopen("DoubleData","r");
  fscanToDeque(fp_in,d_p1);
  fclose(fp_in);

  printf("ファイル入力\n");
  printf("デク１を表示します。\n");
  printDeque(d_p1);
  printf("デク２を表示します。\n");
  printDeque(d_p2);

  copyDeque(d_p1,d_p2);
  printf("デクの複製\n");
  printf("デク１を表示します。\n");
  printDeque(d_p1);
  printf("デク２を表示します。\n");
  printDeque(d_p2);

  printf("ファイルへ順に出力します。\n");
  fp_out=fopen("Mirror","w");
  forward_fprint(fp_out,d_p1);//ファイルへ順に出力
  printf("ファイルへ逆に出力します。\n");
  reverse_fprint(fp_out,d_p2);//ファイルへ逆順に出力
  fclose(fp_out);

  printf("デク１を表示します。\n");
  printDeque(d_p1);

  printf("デク２を表示します。\n");
  printDeque(d_p2);

  return 0;
}

DoubleDeque makeDeque(){
  DoubleDeque deque;
  deque.head=NULL;
  deque.tail=NULL;
  return deque;
  }

double isEmpty(DoubleDeque *deque){
  if(deque->head==NULL){
    return NODATA;
  }else{
    return EXISTDATA;
  }
}


Cell_P makeCell(double n){
  Cell_P new =(Cell_P)malloc(sizeof(DoubleCell));
  new->data=n;
  return new;
}

void head_in(DoubleDeque *deque,double data){
  Cell_P new_cell=makeCell(data);
  if(isEmpty(deque)==NODATA){
    deque->head=new_cell;
    deque->tail=new_cell;
  }else{
  new_cell->prev=NULL;
  new_cell->next=deque->head;
  deque->head->prev=new_cell;
  deque->head=new_cell;
  }
  return;
}

double head_out(DoubleDeque *deque){
  double idata;
  Cell_P remove;
  if(deque->head!=deque->tail){
    remove=deque->head;
    idata=remove->data;
    deque->head=deque->head->next;
    deque->head->prev=NULL;
    free(remove);
    return idata;
  }else if(deque->head==deque->tail){//最後の一個の削除
    remove=deque->head;
    idata=remove->data;
    deque->head=NULL;
    deque->tail=NULL;
    free(remove);
    return idata;
  }else{
    printf("No data\n");
    return -1;
  }
}

void tail_in(DoubleDeque *deque ,double data){
  Cell_P new_cell=makeCell(data);
  if(isEmpty(deque)==NODATA){
    deque->head=new_cell;
    deque->tail=new_cell;
  }else{
    new_cell->next=NULL;
    new_cell->prev=deque->tail;
    deque->tail->next=new_cell;
    deque->tail=new_cell;
  }
  return ;
}

double tail_out(DoubleDeque *deque){
  double idata;
  Cell_P remove;
  if(deque->tail!=deque->head){
    remove=deque->tail;
    idata=remove->data;
    deque->tail=deque->tail->prev;
    deque->head->next=NULL;
    free(remove);
    return idata;
  }else if(deque->tail==deque->head){//最後の一個の削除
    remove=deque->tail;
    idata=remove->data;
    deque->head=NULL;
    deque->tail=NULL;
    free(remove);
    return idata;
  }else{
    printf("No data\n");
    return -1;
  }
}

void copyDeque(DoubleDeque *deque1,DoubleDeque *deque2){
  Cell_P p1=deque1->head;
  if(deque1->head!=NULL){
    while(p1!=deque1->tail){
      tail_in(deque2,p1->data);
      p1=p1->next;
    }
    tail_in(deque2,p1->data);
  }
  return ;
}

void printDeque(DoubleDeque *deque){
  Cell_P  p=deque->head;
  if(deque->head==NULL){
    printf("()\n");
  }else{
    printf("(");
    while(p!=deque->tail){
      printf("%3f,",p->data);
      p=p->next;
    }
    printf("%3f,",p->data);
    printf(")\n");
  }
  return;
}
void fscanToDeque(FILE *fp,DoubleDeque *deque){
  double idata;
  while(fscanf(fp,"%lf",&idata)!=EOF){
    head_in(deque,idata);
  }
  return;
}

void forward_fprint(FILE*fp,DoubleDeque *deque){
  double idata;
  while(isEmpty(deque)==EXISTDATA){
    idata=tail_out(deque);
    fprintf(fp,"%3f",idata);
  }
  return ;
}

void reverse_fprint(FILE*fp,DoubleDeque *deque){
  double idata;
  while(isEmpty(deque)==EXISTDATA){
    idata=head_out(deque);
    fprintf(fp,"%3f",idata);
  }
  return ;
}


  
  
