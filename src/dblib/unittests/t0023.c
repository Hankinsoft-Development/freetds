#if HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

#include <stdio.h>

#if HAVE_STDLIB_H
#include <stdlib.h>
#endif /* HAVE_STDLIB_H */

#if HAVE_STRING_H
#include <string.h>
#endif /* HAVE_STRING_H */

#include <assert.h>
#include <sqlfront.h>
#include <sqldb.h>

#include "common.h"

static char software_version[] = "$Id: t0023.c,v 1.3 2002-11-01 20:55:50 castellano Exp $";
static void *no_unused_var_warn[] = {software_version,
                                     no_unused_var_warn};


int failed = 0;


int
main(int argc, char *argv[])
{
   LOGINREC   *login;
   DBPROCESS   *dbproc;
   char        cmd[1024];
   int         i;
   DBINT       rowint;
   DBCHAR      rowchar[2];
   DBCHAR      rowdate[32];

   DBINT       rowtype;
   DBINT       computeint;
   DBCHAR      computedate[32];

#if HAVE_MALLOC_OPTIONS
   /*
    * Options for malloc   A- all warnings are fatal, J- init memory to 0xD0,
    * R- always move memory block on a realloc.
    */
   extern char *malloc_options;
   malloc_options = "AJR";
#endif /* HAVE_MALLOC_OPTIONS */

   read_login_info();

   tdsdump_open(NULL);

   fprintf(stdout, "Start\n");
   add_bread_crumb();

   /* Fortify_EnterScope(); */
   dbinit();

   add_bread_crumb();
   dberrhandle( syb_err_handler );
   dbmsghandle( syb_msg_handler );

   fprintf(stdout, "About to logon\n");

   add_bread_crumb();
   login = dblogin();
   DBSETLPWD(login,PASSWORD);
   DBSETLUSER(login,USER);
   DBSETLAPP(login,"t0023");

fprintf(stdout, "About to open\n");

   add_bread_crumb();
   dbproc = dbopen(login, SERVER);
   if (strlen(DATABASE)) dbuse(dbproc,DATABASE);
   add_bread_crumb();

   fprintf(stdout, "Dropping table\n");
   add_bread_crumb();
   dbcmd(dbproc, "drop table #dblib0023");
   add_bread_crumb();
   dbsqlexec(dbproc);
   add_bread_crumb();
   while (dbresults(dbproc)==SUCCEED)
   {
      /* nop */
   }
   add_bread_crumb();

   fprintf(stdout, "creating table\n");
   dbcmd(dbproc, "create table #dblib0023 (col1 int not null,  col2 char(1) not null, col3 datetime not null)");
   dbsqlexec(dbproc);
   while (dbresults(dbproc)==SUCCEED)
   {
      /* nop */
   }

   fprintf(stdout, "insert\n");

   strcpy(cmd, "insert into #dblib0023 values (1, 'A', 'Jan  1 2002 10:00:00AM')");
   fprintf(stdout, "%s\n",cmd);
   dbcmd(dbproc, cmd);
   dbsqlexec(dbproc);
   while (dbresults(dbproc)==SUCCEED)
   {
      /* nop */
   }
   strcpy(cmd, "insert into #dblib0023 values (2, 'A', 'Jan  2 2002 10:00:00AM')");
   fprintf(stdout, "%s\n",cmd);
   dbcmd(dbproc, cmd);
   dbsqlexec(dbproc);
   while (dbresults(dbproc)==SUCCEED)
   {
      /* nop */
   }
   strcpy(cmd, "insert into #dblib0023 values (3, 'A', 'Jan  3 2002 10:00:00AM')");
   fprintf(stdout, "%s\n",cmd);
   dbcmd(dbproc, cmd);
   dbsqlexec(dbproc);
   while (dbresults(dbproc)==SUCCEED)
   {
      /* nop */
   }
   strcpy(cmd, "insert into #dblib0023 values (8, 'B', 'Jan  4 2002 10:00:00AM')");
   fprintf(stdout, "%s\n",cmd);
   dbcmd(dbproc, cmd);
   dbsqlexec(dbproc);
   while (dbresults(dbproc)==SUCCEED)
   {
      /* nop */
   }
   strcpy(cmd, "insert into #dblib0023 values (9, 'B', 'Jan  5 2002 10:00:00AM')");
   fprintf(stdout, "%s\n",cmd);
   dbcmd(dbproc, cmd);
   dbsqlexec(dbproc);
   while (dbresults(dbproc)==SUCCEED)
   {
      /* nop */
   }

   fprintf(stdout, "select\n");
   strcpy(cmd,"select col1, col2, col3 from #dblib0023 order by col2 ");
   strcat(cmd,"compute sum(col1) by col2 ");
   strcat(cmd,"compute max(col3)");
   dbcmd(dbproc,cmd);
   dbsqlexec(dbproc);
   add_bread_crumb();


   if (dbresults(dbproc) != SUCCEED)
   {
      add_bread_crumb();
      failed = 1;
      fprintf(stdout, "Was expecting a result set.\n");
      exit(1);
   }
   add_bread_crumb();


   for (i = 1; i <= dbnumcols(dbproc); i++)
   {
      add_bread_crumb();
      printf ("col %d is %s\n",i,dbcolname(dbproc,i));
      add_bread_crumb();
   }

   add_bread_crumb();
   fprintf(stdout, "binding row columns\n");
   if (SUCCEED != dbbind(dbproc,1,INTBIND,-1,(BYTE *) &rowint))
   {
      failed = 1;
      fprintf(stderr, "Had problem with bind col1\n");
      abort();
   }
   add_bread_crumb();
   if (SUCCEED != dbbind(dbproc,2,STRINGBIND,-1,(BYTE *) rowchar))
   {
      failed = 1;
      fprintf(stderr, "Had problem with bind col2\n");
      abort();
   }
   add_bread_crumb();
   if (SUCCEED != dbbind(dbproc,3,STRINGBIND,-1,(BYTE *) rowdate))
   {
      failed = 1;
      fprintf(stderr, "Had problem with bind col3\n");
      abort();
   }

   add_bread_crumb();

   fprintf(stdout, "testing compute clause 1\n");

   if (dbnumalts(dbproc, 1) != 1) {
      failed = 1;
      fprintf(stderr, "Had problem with dbnumalts 1\n");
      abort();
   }

   if (dbalttype(dbproc, 1, 1) != SYBINT4) {
      failed = 1;
      fprintf(stderr, "Had problem with dbalttype 1, 1\n");
      abort();
   }

   if (dbaltcolid(dbproc, 1, 1) != 1) {
      failed = 1;
      fprintf(stderr, "Had problem with dbaltcolid 1, 1\n");
      abort();
   }

   if (dbaltop(dbproc, 1, 1) != SYBAOPSUM) {
      failed = 1;
      fprintf(stderr, "Had problem with dbaltop 1, 1\n");
      abort();
   }

   if (SUCCEED != dbaltbind(dbproc, 1, 1,INTBIND,-1,(BYTE *) &computeint)) {
      failed = 1;
      fprintf(stderr, "Had problem with dbaltbind 1, 1\n");
      abort();
   }


   add_bread_crumb();

   fprintf(stdout, "testing compute clause 2\n");

   if (dbnumalts(dbproc, 2) != 1) {
      failed = 1;
      fprintf(stderr, "Had problem with dbnumalts 2\n");
      abort();
   }

   if (dbalttype(dbproc, 2, 1) != SYBDATETIME) {
      failed = 1;
      fprintf(stderr, "Had problem with dbalttype 2, 1\n");
      abort();
   }

   if (dbaltcolid(dbproc, 2, 1) != 3) {
      failed = 1;
      fprintf(stderr, "Had problem with dbaltcolid 2, 1\n");
      abort();
   }

   if (dbaltop(dbproc, 2, 1) != SYBAOPMAX) {
      failed = 1;
      fprintf(stderr, "Had problem with dbaltop 2, 1\n");
      abort();
   }

   if (SUCCEED != dbaltbind(dbproc, 2, 1,STRINGBIND,-1,(BYTE *) computedate)) {
      failed = 1;
      fprintf(stderr, "Had problem with dbaltbind 2, 1\n");
      abort();
   }

   add_bread_crumb();

   while((rowtype = dbnextrow(dbproc)) != NO_MORE_ROWS)
   {
      
      if (rowtype == REG_ROW ) {
         printf("gotten a regular row\n");
      }

      if (rowtype == 1 ) {
         printf("gotten a compute row for clause 1\n");
         printf("value of sum(col1) = %d\n", computeint);
      }

      if (rowtype == 2 ) {
         printf("gotten a compute row for clause 2\n");
         printf("value of max(col3) = %s\n", computedate);

      }
   }

   add_bread_crumb();
   dbexit();
   add_bread_crumb();

   fprintf(stdout, "dblib %s on %s\n", 
           (failed?"failed!":"okay"),
           __FILE__);
   return failed ? 1 : 0; 
}
