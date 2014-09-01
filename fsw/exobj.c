/* 
** File:
**   $Id: $
**
** Purpose: Implement the example object (exobj).
**
** Notes
**   1. This serves as an example object that uses a table. It does not perform
**      any realistic funcions.
**
** References:
**   1. OpenSat Object-based Application Developers Guide.
**
**
** $Date: $
** $Revision: $
** $Log: $
*/

/*
** Include Files:
*/

#include <string.h>

#include "app_config.h"
#include "exobj.h"

/*
** Global File Data
*/

static EXOBJ_Class*  ExObj = NULL;

/*
** Local Function Prototypes
*/


/******************************************************************************
** Function: EXOBJ_Constructor
**
*/
void EXOBJ_Constructor(EXOBJ_Class*  ExObjPtr)
{
 
   ExObj = ExObjPtr;

   CFE_PSP_MemSet((void*)ExObj, 0, sizeof(EXOBJ_Class));

} /* End EXOBJ_Constructor() */


/******************************************************************************
** Function: EXOBJ_GetTblPtr
**
*/
const EXOBJ_Table* EXOBJ_GetTblPtr()
{

   return &(ExObj->Table);

} /* End EXOBJ_GetTblPtr() */


/******************************************************************************
** Function:  EXOBJ_ResetStatus
**
*/
void EXOBJ_ResetStatus()
{

   ExObj->EnableDataLoad = TRUE;
   ExObj->TblIndex = 0;
   
   EXOBJ_LoadDataFromTable();

} /* End EXOBJ_ResetStatus() */


/******************************************************************************
** Function: LoadDataFromTable
**
** No range checking is performed on TblIndex.
**
*/
void EXOBJ_LoadDataFromTable(void)
{

   if (ExObj->EnableDataLoad)
   {
      
      ExObj->Data1 = ExObj->Table.Entry[ExObj->TblIndex].Data1;
      ExObj->Data2 = ExObj->Table.Entry[ExObj->TblIndex].Data2;
      ExObj->Data3 = ExObj->Table.Entry[ExObj->TblIndex].Data3;

   } /* End if Data Load Enabled */

} /* End EXOBJ_LoadDataFromTable() */


/******************************************************************************
** Function: EXOBJ_LoadTable
**
*/
boolean EXOBJ_LoadTable(EXOBJ_Table* NewTable)
{

   boolean  RetStatus = TRUE;

   /* 
   ** This is a simple table copy. More complex table loads may have pass/fail 
   ** criteria.
   */

   CFE_PSP_MemCpy(&(ExObj->Table), NewTable, sizeof(EXOBJ_Table));

   return RetStatus;

} /* End EXOBJ_LoadTable() */


/******************************************************************************
** Function: EXOBJ_LoadTableEntry
**
*/
boolean EXOBJ_LoadTableEntry(uint16 EntryId, EXOBJ_TblEntry* NewEntry)
{

   boolean  RetStatus = TRUE;

   /* 
   ** This is a simple table entry copy. More complex table load may have 
   ** pass/fail criteria.
   */

   CFE_PSP_MemCpy(&(ExObj->Table.Entry[EntryId]),NewEntry,sizeof(EXOBJ_TblEntry));

   return RetStatus;

} /* End EXOBJ_LoadTableEntry() */


/******************************************************************************
** Function: EXOBJ_EnableOutputCmd
**
** Enable the ability to load data from the table to the working data buffer.
**
*/
boolean EXOBJ_EnableDataLoadCmd(const CFE_SB_MsgPtr_t MsgPtr)
{

   const EXOBJ_EnableDataLoadCmdParam *CmdParam = (const EXOBJ_EnableDataLoadCmdParam *) MsgPtr;
   boolean  RetStatus = TRUE;

   ExObj->EnableDataLoad = (CmdParam->EnableDataLoad == TRUE);
   if (ExObj->EnableDataLoad)
   {
      CFE_EVS_SendEvent(EXOBJ_CMD_ENA_DATA_LOAD_INFO_EID, CFE_EVS_INFORMATION,"Data load enabled");
   }
   else
   {
      CFE_EVS_SendEvent(EXOBJ_CMD_ENA_DATA_LOAD_INFO_EID, CFE_EVS_INFORMATION,"Data load disabled");
   }

   return RetStatus;

} /* End EXOBJ_EnableDataLoadCmd() */


/******************************************************************************
** Function: EXOBJ_SetTblIndexCmd
**
** Set the table index for the data to be used in the working data buffer.
*/
boolean EXOBJ_SetTblIndexCmd(const CFE_SB_MsgPtr_t MsgPtr)
{

   const EXOBJ_SetTblIndexCmdParam *CmdParam = (const EXOBJ_SetTblIndexCmdParam *) MsgPtr;
   boolean  RetStatus = FALSE;

   if (CmdParam->TblIndex < EXOBJ_TBL_MAX_ENTRY_ID)
   {
      RetStatus = TRUE;
      ExObj->TblIndex = CmdParam->TblIndex;
      CFE_EVS_SendEvent(EXOBJ_CMD_SET_TBL_INDEX_INFO_EID, CFE_EVS_INFORMATION,
                        "Table index set to %d", ExObj->TblIndex);
   }
   else
   {
      CFE_EVS_SendEvent(EXOBJ_CMD_SET_TBL_INDEX_ERR_EID, CFE_EVS_ERROR,
                        "Commanded table index %d is too big. Max table index is %d", 
                        CmdParam->TblIndex, (EXOBJ_TBL_MAX_ENTRY_ID-1));
   }

   return RetStatus;


} /* End EXOBJ_LoadDataCmd() */


/* end of file */
