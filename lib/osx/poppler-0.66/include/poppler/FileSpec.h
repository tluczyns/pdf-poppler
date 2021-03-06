//========================================================================
//
// FileSpec.h
//
// All changes made under the Poppler project to this file are licensed
// under GPL version 2 or later
//
// Copyright (C) 2008 Carlos Garcia Campos <carlosgc@gnome.org>
// Copyright (C) 2017, 2018 Albert Astals Cid <aacid@kde.org>
//
// To see a description of the changes please see the Changelog file that
// came with your tarball or type make ChangeLog if you are building from git
//
//========================================================================

#ifndef FILE_SPEC_H
#define FILE_SPEC_H

#ifdef USE_GCC_PRAGMAS
#pragma interface
#endif

#include "Object.h"

class EmbFile {
public:
  EmbFile(const Object *efStream);
  ~EmbFile();

  EmbFile(const EmbFile &) = delete;
  EmbFile& operator=(const EmbFile &) = delete;

  int size() const { return m_size; }
  const GooString *modDate() const { return m_modDate; }
  const GooString *createDate() const { return m_createDate; }
  const GooString *checksum() const { return m_checksum; }
  const GooString *mimeType() const { return m_mimetype; }
  Object *streamObject() { return &m_objStr; }
  Stream *stream() { return isOk() ? m_objStr.getStream() : NULL; }
  GBool isOk() const { return m_objStr.isStream(); }
  GBool save(const char *path);

private:
  GBool save2(FILE *f);

  int m_size;
  GooString *m_createDate;
  GooString *m_modDate;
  GooString *m_checksum;
  GooString *m_mimetype;
  Object m_objStr;
};

class FileSpec {
public:
  FileSpec(const Object *fileSpec);
  ~FileSpec();

  FileSpec(const FileSpec &) = delete;
  FileSpec& operator=(const FileSpec &) = delete;

  GBool isOk() const { return ok; }

  const GooString *getFileName() const { return fileName; }
  GooString *getFileNameForPlatform();
  const GooString *getDescription() const { return desc; }
  EmbFile *getEmbeddedFile();

private:
  GBool ok;

  Object fileSpec;

  GooString *fileName;         // F, UF, DOS, Mac, Unix
  GooString *platformFileName;
  Object fileStream;           // Ref to F entry in UF
  EmbFile *embFile;
  GooString *desc;             // Desc
};

Object getFileSpecName (const Object *fileSpec);
Object getFileSpecNameForPlatform (const Object *fileSpec);

#endif /* FILE_SPEC_H */
