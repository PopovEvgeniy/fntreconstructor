#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "format.h"

void show_end_message();
void show_intro();
void show_decompile_message();
void command_line_help();
void show_compile_message();
void go_offset(FILE *file,const unsigned long int offset);
unsigned long int get_file_size(FILE *file);
FILE *open_input_file(const char *name);
FILE *create_output_file(const char *name);
void data_dump(FILE *input,FILE *output,const size_t length);
void write_output_file(FILE *input,const char *name,const size_t length);
char *get_string_memory(const size_t length);
size_t get_extension_position(const char *source);
char *get_short_name(const char *name);
char* get_name(const char *name,const char *ext);
FNT prepare_head();
FNT read_fnt_head(FILE *file);
void decompile_fnt(const char *fnt_file_name);
void compile_fnt(const char *pcx_name,const char *text_file,const char *fnt_file);

int main(int argc, char *argv[])
{
 show_intro();
 switch (argc)
 {
  case 2:
  decompile_fnt(argv[1]);
  break;
  case 4:
  compile_fnt(argv[1],argv[2],argv[3]);
  break;
  default:
  command_line_help();
  break;
 }
 return 0;
}

void show_end_message()
{
 puts(" ");
 puts("Work finish");
}

void show_intro()
{
 puts(" ");
 puts("FNT RECONSTRUCTOR");
 puts("Version 0.6.3");
 puts("Mugen font tool by Popov Evgeniy Alekseyevich, 2011-2018 year");
 puts("This program distributed under GNU GENERAL PUBLIC LICENSE");
}

void show_decompile_message()
{
 puts(" ");
 puts("Extracting a font data...");
}

void command_line_help()
{
 puts("You give a wrong command line arguments!");
 puts("Command line argument for decompiling a font: font file");
 puts("Command line arguments for compiling a font: graphic file, text file, font file");
}

void show_compile_message()
{
 puts(" ");
 puts("Creating a font file.Please wait...");
}

void go_offset(FILE *file,const unsigned long int offset)
{
 fseek(file,offset,SEEK_SET);
}

unsigned long int get_file_size(FILE *file)
{
 unsigned long int length;
 fseek(file,0,SEEK_END);
 length=ftell(file);
 rewind(file);
 return length;
}

FILE *open_input_file(const char *name)
{
 FILE *file;
 file=fopen(name,"rb");
 if (file==NULL)
 {
  puts(" ");
  puts("File operation error");
  exit(1);
 }
 return file;
}

FILE *create_output_file(const char *name)
{
 FILE *file;
 file=fopen(name,"wb");
 if (file==NULL)
 {
  puts(" ");
  puts("File operation error");
  exit(1);
 }
 return file;
}

void data_dump(FILE *input,FILE *output,const size_t length)
{
 unsigned char single_byte;
 size_t index;
 unsigned char *buffer=NULL;
 buffer=(unsigned char*)calloc(length,sizeof(unsigned char));
 if (buffer==NULL)
 {
  for(index=0;index<length;++index)
  {
   fread(&single_byte,1,1,input);
   fwrite(&single_byte,1,1,output);
  }

 }
 else
 {
  fread(buffer,length,1,input);
  fwrite(buffer,length,1,output);
  free(buffer);
 }

}

void write_output_file(FILE *input,const char *name,const size_t length)
{
 FILE *output;
 output=create_output_file(name);
 data_dump(input,output,length);
 fclose(output);
}

char *get_string_memory(const size_t length)
{
 char *memory=NULL;
 memory=(char*)calloc(length+1,sizeof(char));
 if(memory==NULL)
 {
  puts(" ");
  puts("Can't allocate memory");
  exit(1);
 }
 return memory;
}

size_t get_extension_position(const char *source)
{
 size_t index;
 for(index=strlen(source);index>0;--index)
 {
  if(source[index]=='.')
  {
   break;
  }

 }
 if (index==0) index=strlen(source);
 return index;
}

char *get_short_name(const char *name)
{
 size_t length;
 char *result=NULL;
 length=get_extension_position(name);
 result=get_string_memory(length);
 strncpy(result,name,length);
 return result;
}

char* get_name(const char *name,const char *ext)
{
 char *result=NULL;
 size_t length;
 length=strlen(name)+strlen(ext);
 result=get_string_memory(length);
 strcpy(result,name);
 return strcat(result,ext);
}

void write_head(FNT head,FILE *output)
{
 fwrite(&head,sizeof(FNT),1,output);
}

FNT prepare_head()
{
 FNT fnt_head;
 memset(&fnt_head,0,sizeof(FNT));
 strncpy(fnt_head.signature,"ElecbyteFnt",12);
 strncpy(fnt_head.comment,"This font is created by FONT BULDER    ",40);
 fnt_head.pcx_offset=(unsigned long int)sizeof(FNT);
 return fnt_head;
}

FNT read_fnt_head(FILE *file)
{
 FNT fnt;
 fread(&fnt,sizeof(FNT),1,file);
 if (strcmp(fnt.signature,"ElecbyteFnt")!=0)
 {
  puts(" ");
  puts("Bad signature of a font file");
  exit(3);
 }
 return fnt;
}

void decompile_fnt(const char *fnt_file_name)
{
 FILE *fnt_file;
 char *output_file_name;
 char *short_name=NULL;
 FNT fnt;
 fnt_file=open_input_file(fnt_file_name);
 fnt=read_fnt_head(fnt_file);
 show_decompile_message();
 go_offset(fnt_file,fnt.pcx_offset);
 short_name=get_short_name(fnt_file_name);
 output_file_name=get_name(short_name,".pcx");
 write_output_file(fnt_file,output_file_name,(size_t)fnt.pcx_size);
 free(output_file_name);
 output_file_name=get_name(short_name,".txt");
 go_offset(fnt_file,fnt.text_offset);
 write_output_file(fnt_file,output_file_name,(size_t)fnt.text_size);
 free(output_file_name);
 free(short_name);
 show_end_message();
}

void compile_fnt(const char *pcx_name,const char *text_file,const char *fnt_file)
{
 FILE *input;
 FILE *output;
 FNT head;
 head=prepare_head();
 input=open_input_file(pcx_name);
 show_compile_message();
 head.pcx_size=get_file_size(input);
 head.text_offset=head.pcx_offset+head.pcx_size;
 fclose(input);
 input=open_input_file(text_file);
 head.text_size=get_file_size(input);
 fclose(input);
 output=create_output_file(fnt_file);
 write_head(head,output);
 input=open_input_file(pcx_name);
 data_dump(input,output,(size_t)head.pcx_size);
 fclose(input);
 input=open_input_file(text_file);
 data_dump(input,output,(size_t)head.text_size);
 fclose(input);
 fclose(output);
 show_end_message();
}