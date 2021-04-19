#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/Xutil.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>

#define IS_INDEX(arg) (sizeof(arg[0]))
#define IS_ARRAY(arg) (IS_INDEX(arg) && (((void *) &arg) == ((void *) arg)))
#define SIZE_ARRAY(arr) (IS_ARRAY(arr) ? (sizeof(arr) / sizeof(arr[0])) : 0)

using namespace std;

char* bufStr = new char[256];
char bufChar[1];
char *bufText = new char[256];
char *bufTemp = new char[256];
char *bufDel = new char[256];
   
vector<char*> *vecArr = new vector<char*>();
vector<int> *vecInt = new vector<int>();

int i = 0;
int b = 0;
int m = 0;
int z = 0;
bool check = true;

void SendEvent(Display *d, Window w){
    XEvent event;
    memset(&event, 0, sizeof(event));
    event.type = Expose;
    event.xexpose.display = d;
    XSendEvent(d, w, False, ExposureMask, &event);
}


vector<char*> createVecStr(char* arr, bool check){
   if(check){
    vector<char*>::iterator it;
    vecArr->push_back(arr);
    return *vecArr; 
    }
}

vector<int> createVecInt(int i){
  vecInt->push_back(i);
   return *vecInt;
} 

int deleteInt(vector<int> *vecInt, int z){
    auto it = vecInt->begin();
      int x = (it)[z];
      printf("SIZE i = %d\n", x);
      return x;
}


void printVec(vector<char*> *vecArr, int n){
   auto it = vecArr->begin();
    for(int x = 0; x != vecArr->size(); x++){
        for(int m = 0; m != n; m++){
               cout << " vecArr = " << (it[x])[m] << "; ###";
          }
      }
}


void printArr(char* arr, int n){
    for(int i =0; i<n; i++){
        cout << " array = " << arr[i] << "; ##";
    }
}

 char* deleteArr(vector<char*> *vecArr, int z, int i){
    auto it = vecArr->begin();
    bufStr = (it[z]); 
    for (int k = 0; k != i; k++) {
              bufTemp[k] = bufStr[k];
        }           
    for (int v = 0; v != i; v++) {
              bufStr[v] = bufTemp[v];
        } 
      return bufStr;
}


int main(void) {

Display *d; 
int s; 
Window w;
XEvent ev;
bool quit = false;;
int width, height;
XFontStruct *font;
XCharStruct text;
XGCValues values;
unsigned long valuemask;
GC gc;
 
d = XOpenDisplay(NULL);
   if (d == NULL) {
      fprintf(stderr, "Cannot open display\n");
      exit(1);
    }

s = XDefaultScreen(d);

w = XCreateSimpleWindow(d, XRootWindow(d, s), 10, 10,
                           width=600, height=400, 0,
                           XBlackPixel(d, s),
                           XBlackPixel(d, s));


  if ( (font =  XLoadQueryFont(d, "*Medium*" )) == NULL){
      printf("Font not found!\n");
      exit(1);
  }

values.foreground = XWhitePixel(d, s);
values.font = font->fid;
valuemask = 0;
valuemask |= GCForeground | GCFont;
gc = XCreateGC(d, w, valuemask, &values);

XSelectInput(d, w, ButtonPressMask|ExposureMask|KeyPressMask);
XMapWindow(d, w);
  
   while(!quit) { 

      XNextEvent(d, &ev);
      switch(ev.type) {

        case Expose: {

            if (ev.xexpose.count == 0) { 
              XDrawString(d, w, gc, 22, 20 + b,
                         bufStr, strlen(bufStr));

              /*using XDrawText
              XTextItem Xtext = { buf, i, 10, None };
                XDrawText(d, w, gc, 20 + a, 20 + b,
                         &Xtext, 1 );*/   
             }       
             } break;

        case KeyPress: {
                KeySym symLS;
                KeySym sym = XLookupKeysym(&ev.xkey, 0);
                XIM xim = XOpenIM (d, NULL, NULL, NULL);
                XIC xic = XCreateIC (xim,
                        XNInputStyle, XIMPreeditNothing | XIMStatusNothing,
                        XNClientWindow, w,
                        XNFocusWindow, w, NULL);

                XmbLookupString(xic, &ev.xkey, bufChar, 1, &symLS, 0); 
                /*using XLookupString
                XLookupString(&event.xkey, buff, sizeof(buff), &symLS, 0);*/

                bufStr[i++] = bufChar[0];
                bufText[m++] = bufChar[0];
                
                //XClearWindow(d, w);
                printf("buf = %s\n", bufStr);

          if(sym == XK_BackSpace ) {    
            i = i - 2; 
            m = m - 2; 
            XClearArea(d, w, 10, 8 + b, 1000, 17 , true);

              if(i == -1){
                z = z - 1;
                i = deleteInt(vecInt, z);
                deleteArr(vecArr, z, i);
                b = b - 20;  
                }   

                SendEvent(d, w);
                printf("z = %d, i = %d\n", z, i); 

              } else { 
              SendEvent(d, w);    
              } 
          
          if(sym == XK_Return){
            i = i - 1;
            z = z + 1;
            createVecInt(i);
            char *bufSave = new char[i];
            for (int k = 0; k != i; k++) {
                        bufTemp[k] = bufStr[k];
                    }
                    
            for (int v = 0; v != i; v++) {
                        bufSave[v] = bufTemp[v];
                    }
            printArr(bufSave, i);
            createVecStr(bufSave, check);
            printf("vecSize = %d\n", vecArr->size());
            printVec(vecArr, i);
             
            for (int v = 0; v != i; v++) {
                        bufDel[v] = 0;
                        bufStr[v] = bufDel[v];

                    }
              i = 0;
              b = b + 20;
              m = m - 1; 

            SendEvent(d, w); 
          }

          if(sym == XK_Escape){
            quit = true;
          }

        } break;

        case MappingNotify: {
            XRefreshKeyboardMapping(&ev.xmapping);

      } break;

      XFreeGC (d, gc);
      XFlush(d);
    
    }

   }
   
   delete [] bufText;
   delete [] bufDel;
   delete [] bufTemp;
   delete [] bufStr;
   delete [] bufSave;

   return 0;
}
    
