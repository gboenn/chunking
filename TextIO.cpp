///////////////////////////////////////////
// TextIO.cpp
// Copyright (C) 2018 Georg Boenn
// GNU General Public License version 3.0
// Free Software Foundation
///////////////////////////////////////////

#ifndef __TextIO_h__
#include "TextIO.h"
#endif

#define TEXTREAD 0

#include <string.h>

#include "gc_switch_ssh.h"
#if BOEHM_GC_SWITCH
#define GC_THREADS
//#include "gc/gc_alloc.h"
#include "gc.h"
//#include "gc_cpp.h"

inline void * operator new(size_t n) { return GC_malloc(n); }
inline void operator delete(void *) {}
inline void * operator new[](size_t n) { return GC_malloc(n); }
inline void operator delete[](void *) {}
#endif

TextIO::TextIO(string echoinit)
{
  text_obj = new DList<TextBuf>;
}

TextIO::~TextIO ()
{
  text_obj->destroy ();
  delete text_obj;
}

void TextIO::TextWrite( ofstream &osfptr, string filename )
{
  osfptr.open(filename.c_str(), ios_base::out );
  if( !osfptr ) 
    cerr << "cannot write file: " << filename << endl;
}

void TextIO::TextRead( ifstream &isfptr, string filename )
{
    isfptr.open (filename.c_str(), ios_base::in);
    if (!isfptr) 
	cerr << "no stream. File may not exist: " << filename << endl;
    count = 0;
    
    while (!isfptr.eof()) {
      TextBuf* tb = new TextBuf;
      isfptr.getline( tb->text, MAXTEXTCHARS);
      tb->length = strlen(tb->text);
      text_obj->append (tb);	
      count++;	
    }
}

void TextIO::ReadCommands()
{
  int i = 0;
  for( ; i<kNumModules; i++ )
    {
      TextBuf* tb = new TextBuf;
      strcpy(tb->text, modulTable[i]);
      tb->length = strlen(tb->text);
      text_obj->append (tb);	
    }
  count = kNumModules;
}


string TextIO::GetLine( int line_no )
{
  int i = 0;
  DLink<TextBuf>* tl = text_obj->first ();
  for (; tl!=NULL; tl=tl->next) {
    if (i == line_no) {
      break;
    }
    i++;
  }
  return (tl->data->text);
}


