#!/usr/bin/env python3
 
# 2110352 Operating System
# FUSE/Filesystem exercise
# By Krerk Piromsopa, Ph.D. <Krerk.P@chula.ac.th>
#    Department of Computer Engineering
#    Chulalongkorn University.

import os, stat, errno
import fuse
from fuse import Fuse

if not hasattr(fuse, '__version__'):
    raise RuntimeError("your fuse-py doesn't know of fuse.__version__, probably it's too old.")

fuse.fuse_python_api = (0, 2)

containers={ \
    '/subject':
        b"2021S2 - Operating Systems\nCP ENG CU\n" ,
    '/instructors':
        b"0:CP ENG CU OS 2018S1 - Instructors\n" \
        b"1:      Krerk Piromsopa, Ph. D.\n" \
        b"2:      Veera Muangsin, Ph.D.\n" \
        b"3:      Thongchai Rojkangsadan\n",
    '/students':
        b"0:CP ENG CU OS 2018S1 Students, Group Name: [LigmaBoy]\n" \
        b"1: 6631331621 Naytipat Phothipan\n" \
        b"2: 6632200221 Worralop Srichainont\n" \
        b"3: 6630333721 Sippapas Chavanont\n"
}

class MyStat(fuse.Stat):
   def __init__(self):
       self.st_mode = 0
       self.st_ino = 0
       self.st_dev = 0
       self.st_nlink = 0
       self.st_uid = 0
       self.st_gid = 0
       self.st_size = 0
       self.st_atime = 0
       self.st_mtime = 0
       self.st_ctime = 0

class MyFS(Fuse):

   def getattr(self, path):
       st = MyStat()
       if path == '/':
           st.st_mode = stat.S_IFDIR | 0o777
           st.st_nlink = 2
       elif path in containers:
           st.st_mode = stat.S_IFREG | 0o444

           st.st_nlink = 1
           content=containers[path]
           st.st_size = len(content)
       else:
           return -errno.ENOENT
       return st

   def readdir(self, path, offset):
       filenames=containers.keys()
       for r in  '.', '..':
           yield fuse.Direntry(r)

       for r in filenames:
           yield fuse.Direntry(r[1:])


   def open(self, path, flags):
       if path not in containers:
           return -errno.ENOENT
       accmode = os.O_RDONLY | os.O_WRONLY | os.O_RDWR
       if (flags & accmode) != os.O_RDONLY:
           return -errno.EACCES

   def read(self, path, size, offset):
       if path not in containers:
           return -errno.ENOENT

       content = containers[path]
       slen = len(content)
       if offset < slen:
           if offset + size > slen:
               size = slen - offset
           buf = content[offset:offset+size]
       else:
           buf = ''
       return buf

def main():
    usage="""
Userspace hello example
""" + Fuse.fusage
    server = MyFS(version="%prog " + fuse.__version__,
                     usage=usage,
                     dash_s_do='setsingle')

    server.parse(errex=1)
    server.main()

if __name__ == '__main__':
    main()
