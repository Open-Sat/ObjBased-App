/*
 * File:
 *   $Id: $
 *
 * Purpose: This file contains a unit test cases for tblmgr.c
 *
 * $Date: $
 * $Revision: $
 * $Log: $
 */

/*
 * Includes
 */

#include "common_types.h"
#include "tblmgr.h"
#include "exobj.h"

#include "utassert.h"
#include "uttest.h"
#include "ut_cfe_sb_stubs.h"
#include "ut_cfe_sb_hooks.h"
/* trouble with dirent.h and too lazy to figure it out. I don't use it so redefined DIR */
#define  DIR  char
#include "ut_osfileapi_stubs.h"
#include "ut_cfe_fs_stubs.h"

#define TEST_PIPE_NAME      "Test Pipe"
#define TEST_PIPE_DEPTH     2
#define TEST_OBJ_TBL_LOAD   "exobjtbl.xml"
#define TEST_OBJ_TBL_DUMP   "exobjtbl.txt"
/*
 * File Global Variables
 */

static TBLMGR_Class UtTblMgr;
static EXOBJ_Class UtExObj;

FILE* FilePtr;


/*
 * Function Definitions
 */

int32 UT_fcreate (const char *path, int32  access)
{

   int32 RetStatus;

   /* I only use it for write */
   FilePtr = fopen(path,"w");

   RetStatus = (FilePtr == NULL ? OS_FS_ERROR : OS_FS_SUCCESS);

   return RetStatus;

} /* End UT_fcreate() */

int32 UT_fopen (const char *path,  int32 access,  uint32  mode)
{
   int32 RetStatus;

   /* I only use it for read or write */
   if (access == OS_READ_ONLY)
      FilePtr = fopen(path,"r");
   else
      FilePtr = fopen(path,"w");

   RetStatus = (FilePtr == NULL ? OS_FS_ERROR : OS_FS_SUCCESS);

   printf ("UT_fopen() - Open status = 0x%8X\n",RetStatus);

   return RetStatus;

} /* End UT_FileOpen () */


int32 UT_fclose (int32  filedes)
{

   if (FilePtr != NULL)
   {
      fclose (FilePtr);
      return (OS_FS_SUCCESS);
   }
   return OS_FS_SUCCESS;

} /* End OS_close () */

int32 UT_fread  (int32  filedes, void *buffer, uint32 nbytes)
{

   int32 BytesRead;

   if (FilePtr != NULL)
   {
      BytesRead = (int)fread(buffer, 1, nbytes, FilePtr);
      return (BytesRead);
   }
   return OS_FS_ERROR;

} /* End UT_fread() */



int32 UT_fwrite (int32  filedes, void *buffer, uint32 nbytes)
{

   int32 BytesWritten;

   if (FilePtr != NULL)
   {
      BytesWritten = fwrite(buffer, 1, nbytes, FilePtr);
      return (BytesWritten);
   }
   return OS_FS_ERROR;

} /* End UT_fwrite() */


int32 UT_CFE_FS_WriteHeader(int32 FileDes, CFE_FS_Header_t *Hdr)
{
   printf("UT_CFE_FS_WriteHeader()\n");
   return (UT_fwrite (FileDes, Hdr, sizeof(CFE_FS_Header_t)));
}

/******************************************************************************
** Function: TBLMGR_Test01
**
** - Constructor
**
*/
void TBLMGR_Test01(void)
{

   TBLMGR_DumpTblCmd  DumpTblCmd;

   printf("TBLMGR_Test01()\n");

   EXOBJ_Constructor(&UtExObj);
   printf("TBLMGR_Test01() - A\n");
   TBLMGR_Constructor(&UtTblMgr, TEST_OBJ_TBL_LOAD);

   printf("TBLMGR_Test01()- B\n");

   CFE_PSP_MemCpy((void*)&(DumpTblCmd.FileName),TEST_OBJ_TBL_DUMP, OS_MAX_PATH_LEN);
   TBLMGR_DumpExObjTableCmd((CFE_SB_Msg_t*)&DumpTblCmd);

} /* End TBLMGR_Test01() */

/* TBLMGR_Test02  - TBD Description */
void TBLMGR_Test02(void)
{
   printf("TBLMGR_Test02()\n");
   return;

} /* End TBLMGR_Test01() */

/* initialize test environment to default state for every test */
void TBLMGR_Setup(void)
{

   Ut_OSFILEAPI_Reset();
   Ut_OSFILEAPI_SetFunctionHook(UT_OSFILEAPI_CREAT_INDEX, (void*)UT_fcreate);
   Ut_OSFILEAPI_SetFunctionHook(UT_OSFILEAPI_OPEN_INDEX,  (void*)UT_fopen);
   Ut_OSFILEAPI_SetFunctionHook(UT_OSFILEAPI_READ_INDEX,  (void*)UT_fread);
   Ut_OSFILEAPI_SetFunctionHook(UT_OSFILEAPI_WRITE_INDEX, (void*)UT_fwrite);
   Ut_OSFILEAPI_SetFunctionHook(UT_OSFILEAPI_CLOSE_INDEX, (void*)UT_fclose);

   Ut_CFE_FS_Reset();
   Ut_CFE_FS_SetFunctionHook(UT_CFE_FS_WRITEHDR_INDEX, (void*)UT_CFE_FS_WriteHeader);


} /* TBLMGR_Setup() */

void TBLMGR_TearDown(void)
{
    /* cleanup test environment */
}

void TBLMGR_AddTestCase(void)
{
    UtTest_Add(TBLMGR_Test01, TBLMGR_Setup, TBLMGR_TearDown, "TBLMGR_Test01 - Constructor");
    UtTest_Add(TBLMGR_Test02, TBLMGR_Setup, TBLMGR_TearDown, "TBLMGR_Test02 - TBD Description");
}
