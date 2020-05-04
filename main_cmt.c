#include <gtk/gtk.h>
#include<stdio.h>			
#include <stdlib.h>
#include <string.h>
#include "inc/btree.h"
#include "jrb.h"
#include <gdk/gdkkeysyms.h>

const gchar *a, *b;

GtkWidget *textView, *view1, *view2, *about_dialog, *entry_search;
GtkListStore *list;         //list that store words in user interface
BTA *book=NULL;
static char code[128] = { 0 };

// Cac ham ho tro
void set_textView_text(char * text);  // Set text is buffer being displayed by textView // Phan nghia cua tu

const char* soundex(const char *s); // chuyen sang ma codex
int prefix(const char *big, const char *small); // tra lai 1 neu giong prefix, 0 neu nguoc lai // neu small la prefix cua big return 1
void jrb_to_list(JRB nextWordArray, int number); // Dua tu co prefix giong tu mk dien tu jrb vao list
int insert_insoundexlist(char * soundexlist , char * newword,  char * word, char * soundexWord); // them suggest newword vao soundexlist

//insert_insoundexlist(soundexlist, prevword, word, soundexWord)
// dung trong ham suggest tu
// Cac ham chinh trong ham search
void suggest(char * word,gboolean Tab_pressed); // suggest, dua vao prefix, dung JRB to list ~
gboolean search_suggest(GtkWidget * entry, GdkEvent * event, gpointer No_need); // gioi han ky tu, chi nhan alphabelt va tab 
void Show_message(GtkWindow *parent , GtkMessageType type,  char * mms, char * content); // dua ra thong bao 
void close_window(GtkWidget *widget, gpointer window); 

int btfind(char * word); // dung cho ham search

// VIEW DOWN HERE !!!

static void search(GtkWidget *w, gpointer data); // ham chuc nang search
static void edit( GtkWidget *w, gpointer data ); // ham chuc nang edit
static void add(GtkWidget *w, gpointer data);
static void del(GtkWidget *w, gpointer data);
void tra_tu(GtkWidget widget, gpointer window);
void them_tu(GtkWidget widget, gpointer window);
void xoa_tu(GtkWidget widget, gpointer window);
void about(GtkWidget widget, gpointer window);


int main(int argc, char *argv[])
{
	btinit();
	book= btopn("database",0,1);

    //GTK+
	GtkWidget *window;
	GtkWidget *fixed,*image;
	GtkWidget *btn1,*btn2,*btn3,*btn4,*btn5;

	gtk_init(&argc, &argv);

    //tao cua so
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "E-V Dictionary");
	gtk_window_set_default_size(GTK_WINDOW(window), 600, 338);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    //tao nen
	fixed = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(window), fixed);

    //anh nen
	image = gtk_image_new_from_file("doraemon.jpg");
	gtk_container_add(GTK_CONTAINER(fixed), image);

	btn1 = gtk_button_new_with_label("Tra từ");
	gtk_fixed_put(GTK_FIXED(fixed), btn1, 450, 10);   // Dat btn1 vao toa do 20,20
	gtk_widget_set_size_request(btn1, 100, 40);		 // Set kich thuoc btn1  120 width 50 height
//		gtk_widget_set_tooltip_text(btn1, "Search a word");
	g_signal_connect(G_OBJECT(btn1), "clicked", G_CALLBACK(tra_tu), NULL);

	btn2 = gtk_button_new_with_label("Thêm từ");
	gtk_fixed_put(GTK_FIXED(fixed), btn2, 450, 60);
	gtk_widget_set_size_request(btn2, 100, 40);
//		gtk_widget_set_tooltip_text(btn2, "Add a word");
	g_signal_connect(G_OBJECT(btn2), "clicked", G_CALLBACK(them_tu), NULL);

	btn3 = gtk_button_new_with_label("Xoá từ");
	gtk_fixed_put(GTK_FIXED(fixed), btn3, 450, 110);
	gtk_widget_set_size_request(btn3, 100, 40);
//		gtk_widget_set_tooltip_text(btn3, "Delete a word");
	g_signal_connect(G_OBJECT(btn3), "clicked", G_CALLBACK(xoa_tu), NULL);

	btn4 = gtk_button_new_with_label("Thông tin");
	gtk_fixed_put(GTK_FIXED(fixed), btn4, 450, 160);
   	gtk_widget_set_size_request(btn4, 100, 40);
	g_signal_connect(G_OBJECT(btn4), "clicked", G_CALLBACK(about), NULL);

	btn5 = gtk_button_new_with_label("Thoát");
	gtk_fixed_put(GTK_FIXED(fixed), btn5, 450, 210);
	gtk_widget_set_size_request(btn5, 100, 40);
//		gtk_widget_set_tooltip_text(btn5, "Exit");
	g_signal_connect(G_OBJECT(btn5), "clicked", G_CALLBACK(close_window), window);

	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	gtk_widget_show_all(window);

	gtk_main();

	btcls(book);

	return 0;
}


void set_textView_text(char * text)  // dua tu vao bo nho dem
{
	GtkTextBuffer *buffer;
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView)); //Returns the GtkTextBuffer being displayed by this text view
	if (buffer == NULL)
		buffer = gtk_text_buffer_new(NULL); //initialize the new text buffer
	gtk_text_buffer_set_text(buffer, text, -1);
// Deletes current contents of buffer , and inserts text instead. If len is -1, text must be nul-terminated. text must be valid UTF-8.

	gtk_text_view_set_buffer(GTK_TEXT_VIEW(textView), buffer);
	//Sets buffer as the buffer being displayed by text_view
}

const char* soundex(const char *s) // chuyen sang ma codex
{
	static char out[5];
	int c, prev, i;

	out[0] = out[4] = 0;
	if (!s || !*s) return out;

	out[0] = *s++;

	/* first letter, though not coded, can still affect next letter: Pfister */
	prev = code[(int)out[0]];
	for (i = 1; *s && i < 4; s++) {
		if ((c = code[(int) * s]) == prev) continue;

		if (c == -1) prev = 0;	/* vowel as separator */
		else if (c > 0) {
			out[i++] = c + '0';
			prev = c;
		}
	}
	while (i < 4) out[i++] = '0';
	return out;
}

int prefix(const char *big, const char *small) // tra lai 1 neu giong prefix, 0 neu nguoc lai // neu small la prefix cua big return 1
{
	int small_len = strlen(small);
	int big_len = strlen(big);
	int i;
	if (big_len < small_len)
		return 0;
	for (i = 0; i < small_len; i++)
		if (big[i] != small[i])
			return 0;
		return 1;    
}

void jrb_to_list(JRB nextWordArray, int number)
{
	GtkTreeIter Iter;  // Kieu con tro trong GtkTreeModel // kieu cay trong gtk giup luu tru data // Iter la con tro tron Gtkliststore
  	JRB tmp;
  	int max = 0;
  	jrb_traverse(tmp,nextWordArray){
  		gtk_list_store_append(GTK_LIST_STORE(list), &Iter);
		//Appends a new row to list_store . iter will be changed to point to this new row, the row will be empty
       	gtk_list_store_set(GTK_LIST_STORE(list), &Iter, 0, jval_s(tmp->key), -1 );
		//to set column 0 with type G_TYPE_STRING to “Foo”, you would write gtk_list_store_set (store, iter, 0, "Foo", -1).
    	max++;
    	if (max == 9)
   		   	return;
  	}
}

int insert_insoundexlist(char * soundexlist , char * newword,  char * word, char * soundexWord) // them suggest newword vao soundexlist
{
	if (strcmp(soundexWord, soundex(newword)) == 0) {    // Kiem tra xem newword co ma soundex giong word ko
		if (strcmp(newword, word) != 0) {	// neu newword khac word (ve mat spelling)
			strcat(soundexlist, newword);
			strcat(soundexlist, "\n");
			return 1;
		}
	}
	else
		return 0;
}

//insert_insoundexlist(soundexlist, prevword, word, soundexWord)
// dung trong ham suggest tu

void suggest(char * word,gboolean Tab_pressed) // suggest, dua vao prefix, dung JRB to list ~
{

	char nextword[100], prevword[100];
	int i;
	int max;
	GtkTreeIter Iter;
	JRB tmp, nextWordArray = make_jrb();
	BTint value, existed = 0;
	strcpy(nextword, word);
	int wordlen = strlen(word);
	gtk_list_store_clear(GTK_LIST_STORE(list));
	if (bfndky(book, word, &value) ==  0) { // tim word trong book, value la gia tri cua 'word' tim duoc
		existed = 1;
		gtk_list_store_append(GTK_LIST_STORE(list), &Iter);
		gtk_list_store_set(GTK_LIST_STORE(list), &Iter, 0, nextword, -1 ); // neu dung thi ok
	}
	// neu existed == 1 thi ko can quan tam doan duoi

	if (!existed)
		btins(book, nextword, "", 1); // chen key va data vao B-tree, o key chen blank vao !

	for (i = 0; i < 1945; i++) {
		bnxtky(book, nextword, &value);  // tim 'key' tiep theo    // tra lai key cua con tro tiep theo cua book
		if (prefix(nextword, word)) { // tim nhung nextword ma` word la  prefix cua nextword
			jrb_insert_str(nextWordArray, strdup(nextword), JNULL);  // va chen vao array nextword (de show ra list -> jrb_to_list)
		}
		else break;
	}

	if (!existed && Tab_pressed) { 
		if (jrb_empty(nextWordArray)) {   // Ko co tu nao co prefix la word thi se goi y theo kieu soundex
			char soundexlist[1000] = "Ý bạn là:\n";
			char soundexWord[50];   // soundexWord la ma soundex cua word
			strcpy(nextword, word);   // thu bo xem sao
			strcpy(prevword, word);	  // thu bo xem sao
			strcpy(soundexWord, soundex(word)); // soundex dung de tim tu 'xung quanh'
			max = 5;
			for (i = 0; (i < 10000 ) && max; i++) {				// Can chu y con so 10000 nay
				if (bprvky(book , prevword, &value) == 0)    //bprvky tra lai key cua con tro previous con tro book
					if (insert_insoundexlist(soundexlist, prevword, word, soundexWord))
						max--;
		   	}
			max = 5;
			for (i = 0; (i < 10000 ) && max; i++) {
				if (bnxtky(book, nextword, &value) == 0)
			   		if (insert_insoundexlist(soundexlist, nextword, word, soundexWord))
		   				max--;
			}
			set_textView_text(soundexlist);    // dua soundexlist vao bo nho dem // buffer being displayed by the textView widget
		}
		else {
			int min=1000,tmp_len;
			strcpy(nextword, jval_s(jrb_first(nextWordArray)->key));
		   		//printf("%s\n",nextword );
		   		jrb_traverse(tmp, nextWordArray) {
	   				tmp_len = strlen(jval_s(tmp->key));
	   				if(min > tmp_len)
	   					min = tmp_len;
	   			}
				if ((min != 1000) && (min > wordlen)) {
					jrb_traverse(tmp,nextWordArray){
						if(min == strlen(jval_s(tmp->key)))
							strcpy(nextword,jval_s(tmp->key));
					}
					//printf("%s\n",nextword );
				   	gtk_entry_set_text(GTK_ENTRY(entry_search), nextword);              
			   		gtk_editable_set_position(GTK_EDITABLE(entry_search), min);      
			   	}
		   	}
	}
	else
 		jrb_to_list(nextWordArray, i);         // dua cay jrb nextWordArray ra GtkListStore 
   	if (!existed)
   		btdel(book, word);                    // xoa word trong btree di neu existed !=1
   	jrb_free_tree(nextWordArray);
}

gboolean search_suggest(GtkWidget * entry, GdkEvent * event, gpointer No_need) // gioi han ky tu, chi nhan alphabelt va tab 
{																			   // typedef void* gpointer
	GdkEventKey *keyEvent = (GdkEventKey *)event;   
	char word[50];
	int len;
	strcpy(word, gtk_entry_get_text(GTK_ENTRY(entry_search)));    // copy tu nguoi dung nhap vao thong qua GtkWidget entrySearch

	if (keyEvent->keyval == GDK_KEY_Tab) {
		suggest(word,TRUE);
	}

	if (keyEvent->keyval != GDK_KEY_BackSpace) {   // Neu ko phai phim backspace
   		len = strlen(word);
		word[len] = keyEvent->keyval;
	   	word[len + 1] = '\0';
   	}
   	else {
   		len = strlen(word);
   		word[len - 1] = '\0';
   	}
   	suggest(word,FALSE);
	
	return FALSE;
}

void Show_message(GtkWindow *parent , GtkMessageType type,  char * mms, char * content) // dua ra thong bao 
{
	GtkWidget *mdialog;
	mdialog = gtk_message_dialog_new(parent,
		GTK_DIALOG_DESTROY_WITH_PARENT,
		type,
		GTK_BUTTONS_OK,
		"%s", mms);
	gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(mdialog), "%s",  content);
	gtk_dialog_run(GTK_DIALOG(mdialog));
	gtk_widget_destroy(mdialog);
}

void close_window(GtkWidget *widget, gpointer window) {
	gtk_widget_destroy(GTK_WIDGET(window));
}

int btfind(char * word) // dung cho ham search
{
	char mean[100000];
	int size;

	if(btsel(book,word,mean,100000,&size)==0)
	{
        //gtk_label_set_text(label_print, mean);
		set_textView_text(mean);
		g_print(mean);
		return 1;
	}
    else //gtk_label_set_text(label_print, "Không tồn tại ");
    {
        set_textView_text("Không tồn tại ");
     	return 0;
    }
}

// VIEW DOWN HERE !!!

static void search(GtkWidget *w, gpointer data) // ham chuc nang search
{
	GtkWidget *entry1= ((GtkWidget**)data)[0];
	GtkWidget *window1=((GtkWidget**)data)[1];

	a = gtk_entry_get_text(GTK_ENTRY(entry1));
	g_print("%s\n",a);           // in entry1 ra man hinh      
	char word[50];
	BTint x;

	strcpy(word,a);
	if (word[0] == '\0')		//void Show_message(GtkWindow * parent , GtkMessageType type,  char * mms, char * content)
		Show_message(GTK_WINDOW(window1), GTK_MESSAGE_WARNING, "Cảnh báo!", "Cần nhập từ để tra.");
	else
	{
		int result = btfind(word);
		if (result==0)
			Show_message(GTK_WINDOW(window1),GTK_MESSAGE_ERROR, "Xảy ra lỗi!","Không tìm thấy từ này trong từ điển.");
	}
	return;
}

static void edit( GtkWidget *w, gpointer data ) // ham chuc nang edit
{
	GtkWidget *entry1= ((GtkWidget**)data)[0];                           //GtkWidget *data[3];
	GtkWidget *window1=((GtkWidget**)data)[1];                           //data[0]= entry_search;
	GtkWidget *edit_view=((GtkWidget**)data)[2];						 //data[1]= window1;
																		 //data[2]= textView;
	BTint x;

	if (gtk_entry_get_text(GTK_ENTRY(entry1))[0] == '\0' || bfndky(book, (char*)gtk_entry_get_text(GTK_ENTRY(entry1)), &x) != 0)
	{		// neu chua nhap tu vao entry1 hoac la nhap ko dung tu co trong tu dien vao entry1 thi se hien thi warning
		Show_message(GTK_WINDOW(window1), GTK_MESSAGE_INFO, "Cách dùng:", "Phải tìm kiếm trước khi sửa."); // show_message o tren
		return;
	}

	a = gtk_entry_get_text(GTK_ENTRY(entry1));
	g_print("%s\n",a);
	char word[50],mean[100000];
	strcpy(word,a);

	// Cap nhat Database
	GtkTextBuffer *buffer2;
	GtkTextIter start, end,iter;

	buffer2 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(GTK_TEXT_VIEW(edit_view)));
	//gtk_text_buffer_get_iter_at_offset(buffer2, &iter, 0); //Initializes iter to a position char_offset chars from the start of the entire buffer

	//gtk_text_buffer_insert(buffer2, &iter, "", -1);
	gtk_text_buffer_get_bounds (buffer2, &start, &end);        // Retrieves the first and last iterators in the buffer, i.e. the entire buffer lies within the range [start ,end ).
	b = gtk_text_buffer_get_text (buffer2, &start, &end, FALSE);

	strcpy(mean,b);

	if (word[0] == '\0' || mean[0] == '\0')
		Show_message(GTK_WINDOW(window1), GTK_MESSAGE_WARNING, "Cảnh báo!", "Không được bỏ trống phần nào.");
	else if (bfndky(book, word, &x ) != 0)
		Show_message(GTK_WINDOW(window1), GTK_MESSAGE_ERROR, "Xảy ra lỗi!", "Từ vừa nhập không có trong từ điển.");
	else
	{
		if( btupd(book, word, mean, strlen(mean) + 1)==1)
			Show_message(GTK_WINDOW(window1),GTK_MESSAGE_ERROR, "Xảy ra lỗi!","Không thể cập nhật từ.");
		else
			Show_message(GTK_WINDOW(window1),GTK_MESSAGE_INFO, "Thành công!","Đã cập nhật từ.");
	}

}

static void add(GtkWidget *w, gpointer data)
{

	GtkTextBuffer *buffer1,*buffer2;
	GtkTextIter start, end,iter;
	char mean[10000], word[50];
	buffer1 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(GTK_TEXT_VIEW(view1)));
	gtk_text_buffer_get_iter_at_offset(buffer1, &iter, 0);

	gtk_text_buffer_insert(buffer1, &iter, "", -1);
	gtk_text_buffer_get_bounds (buffer1, &start, &end);
	b = gtk_text_buffer_get_text (buffer1, &start, &end, FALSE);

	strcpy(word,b);
	g_print(word);

	buffer2 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(GTK_TEXT_VIEW(view2)));
	//gtk_text_buffer_get_iter_at_offset(buffer2, &iter, 0);

	//gtk_text_buffer_insert(buffer2, &iter, "", -1);
	gtk_text_buffer_get_bounds (buffer2, &start, &end);
	b = gtk_text_buffer_get_text (buffer2, &start, &end, FALSE);

	strcpy(mean,b);
	printf("\n");
	g_print(mean);

	BTint x;

	if (word[0] == '\0' || mean[0] == '\0')
		Show_message(GTK_WINDOW(data), GTK_MESSAGE_WARNING, "Cảnh báo!", "Không được bỏ trống phần nào.");
	else if (bfndky(book, word, &x ) == 0)
		Show_message(GTK_WINDOW(data), GTK_MESSAGE_ERROR, "Xảy ra lỗi!", "Từ vừa nhập đã có trong từ điển.");
	else
	{
		if(btins(book,word, mean,10000))
			Show_message(GTK_WINDOW(data),GTK_MESSAGE_ERROR, "Xảy ra lỗi!","Không thể thêm vào từ điển.");
		else
			Show_message(GTK_WINDOW(data),GTK_MESSAGE_INFO, "Thành công!","Đã thêm vào từ điển.");
	}

	return;
}

static void del(GtkWidget *w, gpointer data)
{
	GtkWidget *entry1 = ((GtkWidget**)data)[0];
	GtkWidget *window1 = ((GtkWidget**)data)[1];

	a = gtk_entry_get_text(GTK_ENTRY(entry1));
	g_print("%s\n",a);
	char mean[10000], word[50];
	int size;
	BTint x;
	strcpy(word,a);
	if (word[0] == '\0')
		Show_message(GTK_WINDOW(window1), GTK_MESSAGE_WARNING, "Cảnh báo!", "Cần nhập từ muốn xoá.");
	else if (bfndky(book, word, &x ) != 0)
		Show_message(GTK_WINDOW(window1), GTK_MESSAGE_ERROR, "Xảy ra lỗi!", "Từ vừa nhập không có trong từ điển.");
	else
		if(btsel(book,word,mean,100000,&size)==0)
		{
			btdel(book,word);
			Show_message(GTK_WINDOW(window1),GTK_MESSAGE_INFO, "Thành công!","Đã xoá từ khỏi từ điển.");

		}
		else
			Show_message(GTK_WINDOW(window1),GTK_MESSAGE_ERROR, "Xảy ra lỗi!","Không thể xoá từ khỏi từ điển.");


		return;
}

void tra_tu(GtkWidget widget, gpointer window)
{
	GtkWidget *grid,*fixed;
   	GtkWidget *btn1,*window1,*label,*entry,*btn2,*btn3,*label2,*label3;
	window1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);

   	gtk_window_set_title(GTK_WINDOW(window1), "Tra từ");
	gtk_window_set_default_size(GTK_WINDOW(window1), 750, 400);
	gtk_window_set_position(GTK_WINDOW(window1), GTK_WIN_POS_CENTER);  //The window is put in the center of the screen

   	fixed = gtk_fixed_new();          // Khoi tao he toa do
   	gtk_container_add(GTK_CONTAINER(window1), fixed);  // Gan he toa do cho window1

   	grid = gtk_grid_new();										//change GTK_TABLE to GTK_GRID to prevent warning
   	gtk_grid_set_row_spacing(GTK_GRID(grid),15);				//Sets the amount of space between rows of grid
   	gtk_container_add(GTK_CONTAINER(fixed), grid);

   	label = gtk_label_new("Nhập:");                             // Kieu label ko co khung
   	gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);			//attach a grid 

   	entry_search = gtk_entry_new();                             // Kieu entry la o de nhap tu
   	gtk_widget_set_size_request(entry_search, 300, 30);
   	gtk_entry_set_max_length(GTK_ENTRY(entry_search),100);      // Set do dai max cua entry_search

   	gtk_grid_attach_next_to(GTK_GRID(grid), entry_search, label, GTK_POS_RIGHT, 2, 1); //attach a grid next to another grid 
   															//attach entry search on the right-hand label
   	GtkEntryCompletion *comple = gtk_entry_completion_new();
   	gtk_entry_completion_set_text_column(comple, 0);
   	list = gtk_list_store_new(10, G_TYPE_STRING, G_TYPE_STRING,
   		G_TYPE_STRING, G_TYPE_STRING,
   		G_TYPE_STRING, G_TYPE_STRING,
   		G_TYPE_STRING, G_TYPE_STRING,
   		G_TYPE_STRING, G_TYPE_STRING);
   	gtk_entry_completion_set_model(comple, GTK_TREE_MODEL(list));  // set the model for the gtk_entry_completion
   	gtk_entry_set_completion(GTK_ENTRY(entry_search), comple);

   	btn1 = gtk_button_new_with_label("Tra");
   	gtk_fixed_put(GTK_FIXED(fixed), btn1, 450, 15);
   	gtk_widget_set_size_request(btn1, 80, 30);

   	label2 = gtk_label_new("Nghĩa:");
   	gtk_grid_attach_next_to(GTK_GRID(grid), label2, label, GTK_POS_BOTTOM, 1, 20); //attach label"Nghia" on the bottom of "Nhap"

   	textView = gtk_text_view_new();
   	gtk_widget_set_size_request(textView, 300, 300);
   	gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(textView), GTK_WRAP_WORD);  //Sets the line wrapping for the view.
																		  //GTK_WRAP_WORD: wrap text, breaking lines in between words
   	GtkWidget *scrolling = gtk_scrolled_window_new(NULL, NULL);
   	gtk_container_add(GTK_CONTAINER(scrolling), textView);    // textView is linked to the "Nghia cua tu"

   	gtk_grid_attach_next_to(GTK_GRID(grid), scrolling, label2, GTK_POS_RIGHT,2,20); //attach window.scrolled on the right of label "Nghia"

   	btn2 = gtk_button_new_with_label("Trở về");
   	gtk_fixed_put(GTK_FIXED(fixed), btn2, 550, 15);
   	gtk_widget_set_size_request(btn2, 80, 30);

   	btn3 = gtk_button_new_with_label("Cập nhật nghĩa của từ");
   	gtk_fixed_put(GTK_FIXED(fixed), btn3, 450, 100);
   	gtk_widget_set_size_request(btn3, 180, 30);

   	label3 = gtk_label_new("Cách dùng: \n\t Tra từ \n\t-> Sửa nghĩa của từ \n\t-> Cập nhật từ");
   	gtk_fixed_put(GTK_FIXED(fixed), label3, 450, 150);

   	GtkWidget *data[3];
   	data[0]= entry_search;
   	data[1]= window1;
   	data[2]= textView;

   	g_signal_connect(entry_search, "key-press-event", G_CALLBACK(search_suggest), NULL);

   	g_signal_connect(G_OBJECT(entry_search), "activate", G_CALLBACK(search), data);

   	g_signal_connect(G_OBJECT(btn1), "clicked", G_CALLBACK(search), data);

   	g_signal_connect(G_OBJECT(btn2), "clicked", G_CALLBACK(close_window), window1);

   	g_signal_connect(G_OBJECT(btn3), "clicked", G_CALLBACK(edit), data);

   	g_signal_connect(G_OBJECT(window1), "destroy", G_CALLBACK(gtk_main_quit), NULL);

   	gtk_widget_show_all(window1);

   	gtk_main();

   	return;

}

void them_tu(GtkWidget widget, gpointer window)
{
   	GtkWidget *grid,*fixed, *btn2;
   	GtkWidget *btn1,*window1,*label1,*entry1,*label2,*entry2;

   	window1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   	gtk_window_set_title(GTK_WINDOW(window1), "Thêm từ");
   	gtk_window_set_default_size(GTK_WINDOW(window1), 700, 400);
   	gtk_window_set_position(GTK_WINDOW(window1), GTK_WIN_POS_CENTER);

   	fixed = gtk_fixed_new();
   	gtk_container_add(GTK_CONTAINER(window1), fixed);

   	grid = gtk_grid_new();								
   	gtk_grid_set_row_spacing(GTK_GRID(grid),15);
   	gtk_container_add(GTK_CONTAINER(fixed), grid);

   	label1 = gtk_label_new("Từ:");
   	gtk_grid_attach(GTK_GRID(grid), label1, 0, 0, 1, 1);

   	view1 = gtk_text_view_new();
   	gtk_widget_set_size_request(view1, 300, 20);
   	gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(view1), GTK_WRAP_WORD);
   	gtk_grid_attach_next_to(GTK_GRID(grid), view1, label1, GTK_POS_RIGHT, 2, 1);

   	label2 = gtk_label_new("Nghĩa:");
   	gtk_grid_attach_next_to(GTK_GRID(grid), label2, label1, GTK_POS_BOTTOM, 1, 20);

   	view2 = gtk_text_view_new();
   	gtk_widget_set_size_request(view2, 300, 300);
   	gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(view2), GTK_WRAP_WORD);

   	GtkWidget *scrolling = gtk_scrolled_window_new(NULL, NULL);
   	gtk_container_add(GTK_CONTAINER(scrolling), view2);
   	gtk_grid_attach_next_to(GTK_GRID(grid), scrolling, label2, GTK_POS_RIGHT,2, 20);

   	btn1 = gtk_button_new_with_label("Thêm");
   	gtk_fixed_put(GTK_FIXED(fixed), btn1, 450, 15);
   	gtk_widget_set_size_request(btn1, 80, 30);

   	g_signal_connect(G_OBJECT(btn1), "clicked", G_CALLBACK(add), NULL);

   	btn2 = gtk_button_new_with_label("Trở về");
   	gtk_fixed_put(GTK_FIXED(fixed), btn2, 550, 15);
   	gtk_widget_set_size_request(btn2, 80, 30);

   	g_signal_connect(G_OBJECT(btn2), "clicked", G_CALLBACK(close_window), window1);

   	g_signal_connect(G_OBJECT(window1), "destroy", G_CALLBACK(gtk_main_quit), NULL);

   	gtk_widget_show_all(window1);

   	gtk_main();

   	return;

}

void xoa_tu(GtkWidget widget, gpointer window)
{
   	GtkWidget *grid,*fixed;
   	GtkWidget *btn1,*window1,*label,*entry,*btn2;

   	window1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   	gtk_window_set_title(GTK_WINDOW(window1), "Xoá từ");
   	gtk_window_set_default_size(GTK_WINDOW(window1), 700, 150);
   	gtk_window_set_position(GTK_WINDOW(window1), GTK_WIN_POS_CENTER);

   	fixed = gtk_fixed_new();
   	gtk_container_add(GTK_CONTAINER(window1), fixed);

   	grid = gtk_grid_new();
   	gtk_container_add(GTK_CONTAINER(fixed), grid);

	label = gtk_label_new("Nhập:");
   	gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);

   	entry = gtk_entry_new();
   	gtk_widget_set_size_request(entry, 300, 30);
   	gtk_entry_set_max_length(GTK_ENTRY(entry),100);
   	gtk_grid_attach(GTK_GRID(grid), entry, 1, 0, 2, 1);

   	btn1 = gtk_button_new_with_label("Xoá");
   	gtk_fixed_put(GTK_FIXED(fixed), btn1, 450, 15);
   	gtk_widget_set_size_request(btn1, 80, 30);

   	GtkWidget *data[2];
   	data[0]= entry;
   	data[1]= window1;

	g_signal_connect(G_OBJECT(btn1), "clicked", G_CALLBACK(del), data);

   	g_signal_connect(G_OBJECT(entry), "activate", G_CALLBACK(del), data);

   	btn2 = gtk_button_new_with_label("Trở về");
   	gtk_fixed_put(GTK_FIXED(fixed), btn2, 550, 15);
   	gtk_widget_set_size_request(btn2, 80, 30);

   	g_signal_connect(G_OBJECT(btn2), "clicked", G_CALLBACK(close_window), window1);

   	g_signal_connect(G_OBJECT(window1), "destroy", G_CALLBACK(gtk_main_quit), NULL);

   	gtk_widget_show_all(window1);

   	gtk_main();

   	return;

}

void about(GtkWidget widget, gpointer window)
{
	about_dialog = gtk_about_dialog_new();
	gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(about_dialog), "Từ điển Anh Việt");
	gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(about_dialog), "Đào Đăng Huy 20176782\n Lê Hoàng Mạnh 20176815\n ");
	gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(about_dialog),
		"https://soict.hust.edu.vn/index.php/our_team/ths-ngo-van-linh/");
	gtk_about_dialog_set_website_label(GTK_ABOUT_DIALOG(about_dialog), "Contact for Ths.Ngô Văn Linh");     
	gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(about_dialog), "Nhóm hotboy - Việt Nhật A - K62");
	gtk_about_dialog_set_logo_icon_name(GTK_ABOUT_DIALOG(about_dialog), NULL);
	gtk_dialog_run(GTK_DIALOG(about_dialog));
	gtk_widget_destroy(about_dialog);
}