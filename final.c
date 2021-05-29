#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <dos.h>
#include <string.h>
#include <graphics.h>
#include <conio.h>

int gdriver=DETECT,gmode=0,errorcode;
char element[3],ele[3];
int x=1,maxx,midx,xcoord,ycoord,level=320;
struct node
{
   int data;
   struct node *right,*left;
   int hght;
};
void GDisplay(struct node* p,int xcoord,int ycoord)
{
  if (p!=NULL)
	{
	   level=level/2;
	   setfillstyle(1,BROWN);
	   setcolor(LIGHTGREEN);
	   if(p->left->data!=NULL)
		line(xcoord,ycoord,xcoord-level,ycoord+50);
	   if(p->right->data!=NULL)
		line(xcoord,ycoord,xcoord+level,ycoord+50);
	   fillellipse(xcoord,ycoord,10,10);
	   sprintf(element,"%d",p->data,xcoord,ycoord);
	   sprintf(ele,"%d",balancedfac(p),xcoord,ycoord);
	   settextstyle(2,0,4);
	   setcolor(YELLOW);
	   outtextxy(xcoord-7,ycoord-7,element);
	   outtextxy(xcoord-20,ycoord-8,ele);
	   GDisplay(p->left,xcoord-(level),ycoord+50);
	   GDisplay(p->right,xcoord+(level),ycoord+50);
	   level=level*2;
	}
}
int height(struct node* t)
{
	int lf,rf;
	if(t==NULL)
	  return 0;
	if(t->left==NULL)
	  lf=0;
	else
	  lf=1+t->left->hght;
	if(t->right==NULL)
	  rf=0;
	else
	  rf=1+t->right->hght;
    if((lf>rf))
       return(lf);
    else
        return(rf);

}
struct node* roleft(struct node* k)
{
  struct node* j;
  j=k->right;
  k->right=j->left;
  j->left=k;
  k->hght=height(k);
  j->hght=height(k);
  return(j);
}
struct node* roright(struct node* k)
{
  struct node* j;
  j=k->left;
  k->left=j->right;
  j->right=k;
  k->hght=height(k);
  j->hght=height(k);
  return(j);
}
struct node* rr(struct node* k)
{
 k=roleft(k);
 return(k);
}
struct node* ll(struct node* k)
{
 k=roright(k);
 return(k);
}
struct node* rl(struct node* k)
{
 k->right=roright(k->right);
 k=roleft(k);
 return(k);
}
struct node* lr(struct node* k)
{
 k->left=roleft(k->left);
 k=roright(k);
 return(k);
}
void print(int x,int y,int color,char string[]){
 textcolor(color);
 gotoxy(x,y);
 cprintf("%s",string);
}
int balancedfac(struct node* t)
{
	int lf,rf;
	if(t==NULL)
	  return 0;
	if(t->left==NULL)
	  lf=0;
	else
	  lf=1+t->left->hght;
	if(t->right==NULL)
	  rf=0;
	else
	  rf=1+t->right->hght;
    return(lf-rf);
}

struct node* deletion(struct node* t,int c)
{
    struct node* p=NULL;
    if(t==NULL)
        return NULL;
    else if(c > t->data)
    {
        t->right=deletion(t->right,c);
        if(balancedfac(t)==2)
            if(balancedfac(t->left)>=0)
               t=ll(t);
             else
                t=lr(t);
    }
   else if(c < t->data)
    {
        t->left=deletion(t->left,c);
        if(balancedfac(t)==-2)
            if(balancedfac(t->right)<=0)
               t=rr(t);
             else
                t=rl(t);
    }
    else
    {
        if(t->right!=NULL)
        {
            p=t->right;
         while(p->left!=NULL)
            p=p->left;
         t->data=p->data;
         t->right=deletion(t->right,p->data);
          if(balancedfac(t)==2)
            if(balancedfac(t->left)>=0)
               t=ll(t);
             else
                t=lr(t);
            }
        else
            return(t->left);
        }
t->hght=height(t);
return(t);
}
struct node* insert(struct node* y,int a)
{
if(y==NULL)
{
y=(struct node*)malloc(sizeof(struct node));
y->data=a;
y->right=NULL;
y->left=NULL;
}
else if(a<y->data)
   {
     y->left=insert(y->left,a);
     if(balancedfac(y)==2)
        if(a<y->left->data)
          y=ll(y);
        else
          y=lr(y);
   }
else if(a>y->data)
  {
    y->right=insert(y->right,a);
    if(balancedfac(y)==-2)
        if(a>y->right->data)
          y=rr(y);
        else
          y=rl(y);
  }
  else
  {
    gotoxy(2,21);
    printf("Same element given");
  }
y->hght=height(y);
return(y);
}

void main()
{

int k=0,l=0,b=0,i=0;
char n;
struct node *y= NULL;
do
{
 clrscr();
 print(20,3,GREEN,"a- Both Creation and Insertion");
 print(20,4,GREEN,"b- Deletion");
 print(20,5,GREEN,"c- Display");
 print(20,7,GREEN,"d-end");
 print(20,11,LIGHTRED,"Enter your choice ");
 n=getch();
switch(n)
{
    case 'a': gotoxy(2,14);
              printf("enter how many elements to be in the tree:");
              scanf("%d",&k);
                for(i=0;i<k;i++)
                {
                printf("Enter the data:");
                scanf("%d",&l);
                y=insert(y,l);
                }
                print(20,20,YELLOW,"Tree created");
                getch();
			     initgraph(&gdriver,&gmode,"c:\tc\bgi");
                 errorcode = graphresult();
                if (errorcode != grOk)
			              {
			                  printf("Graphics error:" "%s", grapherrormsg(errorcode));
                              printf("Press any key to stop");
			                  getch();
                            exit(1);
			                  }
                maxx=getmaxx();
                midx=maxx/2;xcoord=midx/2;ycoord=40;
                cleardevice();
                setbkcolor(LIGHTBLUE);
                GDisplay(y,midx,50);
                getch();
			    restorecrtmode();
                 break;
          case  'b':if(y==NULL)
                     {
                       break;
                     }
                 else
                {
                 gotoxy(2,14);
                 printf("enter the data to be deleted:");
                 scanf("%d",&b);
                 y=deletion(y,b);
                 getch();
			     initgraph(&gdriver,&gmode,"c:\tc\bgi");
                 errorcode = graphresult();
                if (errorcode != grOk)
			              {
			                  printf("Graphics error:" "%s", grapherrormsg(errorcode));
                              printf("Press any key to stop");
			                  getch();
                            exit(1);
			                  }
                maxx=getmaxx();
                midx=maxx/2;xcoord=midx/2;ycoord=40;
                cleardevice();
                setbkcolor(LIGHTBLUE);
                GDisplay(y,midx,50);
                getch();
			  restorecrtmode();
			  print(20,14,YELLOW,"data deleted");
                }
			  break;
   case 'c':initgraph(&gdriver,&gmode,"c:\tc\bgi");
                 errorcode = graphresult();
                if (errorcode != grOk)
			              {
			                  printf("Graphics error: %s", grapherrormsg(errorcode));
                              printf("Press any key to stop");
			                  getch();
                            exit(1);
			                  }
                maxx=getmaxx();
                midx=maxx/2;xcoord=midx/2;ycoord=40;
                cleardevice();
                setbkcolor(LIGHTBLUE);
                GDisplay(y,midx,50);
                getch();
			  restorecrtmode();
			  break;
   default:printf("Try again");
}
}while(n!='d');
}
