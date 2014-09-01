/*
** $Id: $
** 
** Purpose: Implement an example object.
**
** Notes:
**   1. This object is for illustrative purposes only and is not designed as a
**      template because it contains too  much non-generic functionality.
**   2. It defines an array of data tuples (Data1, Data2, Data3). The user can
**      select which data tuple is loaded from the table into the working data
**      variables.
**
** References:
**   1. CFS Object-based Application Developers Guide.
**
** $Date: $
** $Revision: $
** $Log: $
**
*/

#ifndef _exobj_
#define _exobj_

/*
** Includes
*/

#include "app_config.h"
#include "common_types.h"
#include "cfe.h"


/*
** Event Message IDs
*/

#define EXOBJ_CMD_ENA_DATA_LOAD_INFO_EID   (EXOBJ_BASE_EID + 0)
#define EXOBJ_CMD_SET_TBL_INDEX_INFO_EID   (EXOBJ_BASE_EID + 1)
#define EXOBJ_CMD_SET_TBL_INDEX_ERR_EID    (EXOBJ_BASE_EID + 2)


/*
** Type Definitions
*/

/******************************************************************************
** Packet Table
*/

typedef struct {

   uint16   Data1;
   uint16   Data2;
   uint16   Data3;

} EXOBJ_TblEntry;

typedef struct
{
	EXOBJ_TblEntry Entry[EXOBJ_TBL_MAX_ENTRY_ID];

} EXOBJ_Table;


/******************************************************************************
** ExObj_Class
*/

typedef struct {

   boolean    EnableDataLoad;
   uint16     TblIndex;
   uint16     Data1;
   uint16     Data2;
   uint16     Data3;

   EXOBJ_Table   Table;

} EXOBJ_Class;


/******************************************************************************
** Command Functions
*/

typedef struct
{

   uint8     CmdHeader[CFE_SB_CMD_HDR_SIZE];
   boolean   EnableDataLoad;

} EXOBJ_EnableDataLoadCmdParam;
#define EXOBJ_ENABLE_DATA_LOAD_CMD_DATA_LEN  (sizeof(EXOBJ_EnableDataLoadCmdParam) - CFE_SB_CMD_HDR_SIZE)


typedef struct
{

   uint8    CmdHeader[CFE_SB_CMD_HDR_SIZE];
   uint16   TblIndex;  

}  EXOBJ_SetTblIndexCmdParam;
#define EXOBJ_SET_TBL_INDEX_CMD_DATA_LEN  (sizeof(EXOBJ_SetTblIndexCmdParam) - CFE_SB_CMD_HDR_SIZE)

/*
** Exported Functions
*/

/******************************************************************************
** Function: EXOBJ_Constructor
**
** Construct exobj. All table entries are cleared and the LoadTable()
** function should be used to load an initial table.
**
** Notes:
**   1. This must be called prior to any other function.
**   2. Decoupling the initial table load gives an app flexibility in file
**      management during startup.
**
*/
void EXOBJ_Constructor(EXOBJ_Class *ObjPtr);


/******************************************************************************
** Function: EXOBJ_GetTblPtr
**
** Return a pointer to the table.
**
*/
const EXOBJ_Table* EXOBJ_GetTblPtr(void);


/******************************************************************************
** Function: EXOBJ_ResetStatus
**
** Reset counters and status flags to a known reset state.
**
** Notes:
**   1. Any counter or variable that is reported in HK telemetry that doesn't
**      change the functional behavior should be reset.
**
*/
void EXOBJ_ResetStatus(void);


/******************************************************************************
** Function: EXOBJ_LoadDataFromTable
**
** No range checking is performed on TblIndex.
**
*/
void EXOBJ_LoadDataFromTable(void);


/******************************************************************************
** Function: EXOBJ_LoadTable
**
** Loads the entire new table.
**
** Notes:
** 1. No validity checks are performed on the table data.
**
*/
boolean EXOBJ_LoadTable(EXOBJ_Table* NewTable);


/******************************************************************************
** Function: EXOBJ_LoadTableEntry
**
** Load a single table entry
**
** Notes:
**   1. Range checking is not performed on the parameters.
**
*/
boolean EXOBJ_LoadTableEntry(uint16 EntryId, EXOBJ_TblEntry* NewEntry);


/******************************************************************************
** Function: EXOBJ_EnableOutputCmd
**
** Enable the ability to load data from the table to the working data buffer.
**
*/
boolean EXOBJ_EnableDataLoadCmd(const CFE_SB_MsgPtr_t MsgPtr);


/******************************************************************************
** Function: EXOBJ_LoadDataCmd
**
** Load data from the table to the working data buffer.
*/
boolean EXOBJ_SetTblIndexCmd(const CFE_SB_MsgPtr_t MsgPtr);


#endif /* _exobj_ */
