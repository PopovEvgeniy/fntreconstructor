#include "fntreconstructor.h"
#include "format.h"

void show_intro();
void command_line_help();
FILE *open_input_file(const char *name);
FILE *create_output_file(const char *name);
void read_data(void *data,const size_t length,FILE *input);
void write_data(const void *data,const size_t length,FILE *output);
void go_offset(FILE *target,const unsigned long int offset);
char *get_memory(const size_t length);
void check_signature(const char *signature);
unsigned long int get_file_size(FILE *target);
void data_dump(FILE *input,FILE *output,const size_t length);
void fast_data_dump(FILE *input,FILE *output,const size_t length);
void write_output_file(FILE *input,const char *name,const size_t length);
size_t get_name_without_extension_length(const char *source);
char *get_name_without_extension(const char *name);
char *get_name(const char *name,const char *extension);
FNT read_fnt_head(FILE *input);
void write_head(const FNT *head,FILE *output);
FNT prepare_head();
void decompile_font(const char *fnt_file_name);
void compile_font(const char *pcx_name,const char *text_file,const char *fnt_file);

int main(int argc, char *argv[])
{
 show_intro();
 switch (argc)
 {
  case 2:
  puts("Extracting font data...");
  decompile_font(argv[1]);
  puts("The work has been finished");
  break;
  case 4:
  puts("Creating a font file. Please wait...");
  compile_font(argv[1],argv[2],argv[3]);
  puts("The work has been finished");
  break;
  default:
  command_line_help();
  break;
 }
 return 0;
}

void show_intro()
{
 putchar('\n');
 puts("FNT RECONSTRUCTOR");
 puts("Version 1.0.4");
 puts("Mugen font tool by Popov Evgeniy Alekseyevich, 2011-2026 years");
 puts("This program is distributed under the GNU GENERAL PUBLIC LICENSE");
 putchar('\n');
}

void command_line_help()
{
 puts("You give the wrong command-line arguments!");
 puts("The command-line argument for decompiling a font: a font file");
 puts("The command-line arguments for compiling a font: a graphic file, a text file, and the font file");
}

FILE *open_input_file(const char *name)
{
 FILE *target=NULL;
 if (name==NULL)
 {
  puts("Can't open the input file");
  exit(1);
 }
 target=fopen(name,"rb");
 if (target==NULL)
 {
  puts("Can't open the input file");
  exit(1);
 }
 return target;
}

FILE *create_output_file(const char *name)
{
 FILE *target=NULL;
 if (name==NULL)
 {
  puts("Can't create the ouput file");
  exit(2);
 }
 target=fopen(name,"wb");
 if (target==NULL)
 {
  puts("Can't create the ouput file");
  exit(2);
 }
 return target;
}

void read_data(void *data,const size_t length,FILE *input)
{
 fread(data,sizeof(char),length,input);
 if (ferror(input)!=0)
 {
  puts("Can't read data!");
  exit(3);
 }

}

void write_data(const void *data,const size_t length,FILE *output)
{
 fwrite(data,sizeof(char),length,output);
 if (ferror(output)!=0)
 {
  puts("Can't write data!");
  exit(4);
 }

}

void go_offset(FILE *target,const unsigned long int offset)
{
 if (fseek(target,offset,SEEK_SET)!=0)
 {
  puts("Can't jump to the target offset");
  exit(5);
 }

}

char *get_memory(const size_t length)
{
 char *memory=NULL;
 memory=(char*)calloc(length,sizeof(char));
 if(memory==NULL)
 {
  puts("Can't allocate memory");
  exit(6);
 }
 return memory;
}

void check_signature(const char *signature)
{
 if (strncmp(signature,"ElecbyteFnt",12)!=0)
 {
  puts("The invalid format");
  exit(7);
 }

}

unsigned long int get_file_size(FILE *target)
{
 unsigned long int length=0;
 if (fseek(target,0,SEEK_END)!=0)
 {
  puts("Can't get the file size!");
  exit(8);
 }
 length=ftell(target);
 rewind(target);
 return length;
}

void data_dump(FILE *input,FILE *output,const size_t length)
{
 char *buffer=NULL;
 size_t current=0;
 size_t elapsed=0;
 size_t block=4096;
 buffer=get_memory(block);
 for (current=0;current<length;current+=block)
 {
  elapsed=length-current;
  if (elapsed<block)
  {
   block=elapsed;
  }
  read_data(buffer,block,input);
  write_data(buffer,block,output);
 }
 free(buffer);
}

void fast_data_dump(FILE *input,FILE *output,const size_t length)
{
 char *buffer=NULL;
 buffer=(char*)malloc(length);
 if (buffer==NULL)
 {
  data_dump(input,output,length);
 }
 else
 {
  read_data(buffer,length,input);
  write_data(buffer,length,output);
  free(buffer);
 }

}

void write_output_file(FILE *input,const char *name,const size_t length)
{
 FILE *output=NULL;
 output=create_output_file(name);
 fast_data_dump(input,output,length);
 fclose(output);
}

size_t get_name_without_extension_length(const char *source)
{
 size_t index=0;
 size_t position=0;
 size_t length=0;
 if (source!=NULL)
 {
  length=strlen(source);
 }
 for (index=length;index>0;--index)
 {
  position=index-1;
  if (source[position]==DIRECTORY_SEPARATOR)
  {
   break;
  }
  if (source[position]=='.')
  {
   if (position>0)
   {
    if ((source[position-1]!=DIRECTORY_SEPARATOR) && (source[position-1]!='.'))
    {
     length=position;
     break;
    }

   }

  }

 }
 return length;
}

char *get_name_without_extension(const char *name)
{
 char *result=NULL;
 size_t length=0;
 length=get_name_without_extension_length(name);
 if (length>0)
 {
  result=get_memory(length+1);
  strncpy(result,name,length);
 }
 return result;
}

char *get_name(const char *name,const char *extension)
{
  char *result=NULL;
  char *name_without_extension=NULL;
  size_t name_length=0;
  size_t extension_length=0;
  name_without_extension=get_name_without_extension(name);
  if (name_without_extension!=NULL)
  {
   name_length=strlen(name_without_extension);
  }
  if (extension!=NULL)
  {
   extension_length=strlen(extension);
  }
  if ((name_length>0) && (extension_length>0))
  {
   result=get_memory(name_length+extension_length+1);
   strncpy(result,name_without_extension,name_length);
   strncat(result,extension,extension_length);
  }
  free(name_without_extension);
  return result;
}

FNT read_fnt_head(FILE *input)
{
 FNT fnt;
 read_data(&fnt,sizeof(FNT),input);
 check_signature(fnt.signature);
 return fnt;
}

void write_head(const FNT *head,FILE *output)
{
 write_data(head,sizeof(FNT),output);
}

FNT prepare_head()
{
 FNT head;
 strncpy(head.signature,"ElecbyteFnt",12);
 head.signature[11]=0;
 head.version[0]=0;
 head.version[1]=1;
 head.version[2]=0;
 head.version[3]=0;
 head.pcx_offset=sizeof(FNT);
 head.pcx_size=0;
 head.text_offset=0;
 head.text_size=0;
 strncpy(head.comment,"This font was made by FNT RECONSTRUCTOR",39);
 head.comment[39]=0;
 return head;
}

void decompile_font(const char *fnt_file_name)
{
 FILE *fnt_file=NULL;
 char *output_file_name=NULL;
 FNT fnt;
 fnt_file=open_input_file(fnt_file_name);
 fnt=read_fnt_head(fnt_file);
 go_offset(fnt_file,fnt.pcx_offset);
 output_file_name=get_name(fnt_file_name,".pcx");
 write_output_file(fnt_file,output_file_name,(size_t)fnt.pcx_size);
 free(output_file_name);
 go_offset(fnt_file,fnt.text_offset);
 output_file_name=get_name(fnt_file_name,".txt");
 write_output_file(fnt_file,output_file_name,(size_t)fnt.text_size);
 fclose(fnt_file);
 free(output_file_name);
}

void compile_font(const char *pcx_name,const char *text_file,const char *fnt_file)
{
 FILE *pcx=NULL;
 FILE *text=NULL;
 FILE *font=NULL;
 FNT head;
 head=prepare_head();
 pcx=open_input_file(pcx_name);
 text=open_input_file(text_file);
 font=create_output_file(fnt_file);
 head.pcx_size=get_file_size(pcx);
 head.text_size=get_file_size(text);
 head.text_offset=head.pcx_offset+head.pcx_size;
 write_head(&head,font);
 fast_data_dump(pcx,font,(size_t)head.pcx_size);
 fast_data_dump(text,font,(size_t)head.text_size);
 fclose(pcx);
 fclose(text);
 fclose(font);
}