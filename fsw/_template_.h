/*########################### Start Template Block ############################
** This a template file and has been designed to allow template variables to
** be automatically replaced.  Multi-line comment blocks starting with '*##'
** and ending with '##*' (with backslash) can also automatically be replaced.
** They must also include the keywords 'Start' and 'End' in the comments. This
** is required so comment blocks with multiple # signs can also be used to flag
** user tailored (manual) template sections.
**
** All template variables start and end with an underscore. The underscore 
** should be replaced during the substitution process in order to maintain
** compliance with the CFS coding standards. Three case variations of template
** variables are used: upper, mixed, and lower to allow case sensitive
** substitution.
**
** For example to instantiate an application called MYAPP with the case variations
** of (MYAPP, MyApp, and myapp) then type substitutions performed would be: 
** 
**  _TEMPLATE__HkPkt  _Template_HkPkt;  =>  MYAPP_HkPkt  MyAppHkPkt; 
** #ifndef __template__                 =>  _myapp_
** 
** For example to instantiate an object called uplink with the case variations
** of (UPLINK, Uplink, and uplink) then type substitutions performed would be: 
** 
** #define _EXOBJ__Class        =>  UPLINK_Class
** TBLMGR_Load_ExObj_TableCmd   =>  TBLMGR_LoadUplinkTableCmd
** #ifndef __exobj__            =>  _uplink_
**
** Note the template style was chosen to allow the template itself to be 
** compiled and tested.
**
############################# End Template Block ############################*/
/*
** $Id: $
** 
** Purpose: Define the _Template_ application.
**
** Notes:
**   1.
**
** References:
**   1. CFS C Coding Standards
**   2. OpenSat Object-based Application Developers Guide.
**
** $Date: $
** $Revision: $
** $Log: $
**
*/
#ifndef __template__
#define __template__

/*
** Includes
*/

#include "app_config.h"
#include "cmdmgr.h"
#include "tblmgr.h"
#include "exobj.h"

/*
** Macro Definitions
*/

#define _TEMPLATE__INIT_INFO_EID            (_TEMPLATE__BASE_EID + 0)
#define _TEMPLATE__EXIT_ERR_EID             (_TEMPLATE__BASE_EID + 1)
#define _TEMPLATE__CMD_NOOP_INFO_EID        (_TEMPLATE__BASE_EID + 2)
#define _TEMPLATE__CMD_INVALID_MID_ERR_EID  (_TEMPLATE__BASE_EID + 3)

/*
** Type Definitions
*/

typedef struct
{

   CMDMGR_Class CmdMgr;
   TBLMGR_Class TblMgr;
   EXOBJ_Class  ExObj;

   CFE_SB_PipeId_t CmdPipe;

} _TEMPLATE__Class;

typedef struct
{

   uint8    Header[CFE_SB_TLM_HDR_SIZE];

   /*
   ** CMDMGR Data
   */
   uint16   ValidCmdCnt;
   uint16   InvalidCmdCnt;

   /*
   ** TBLMGR Data
   */

   boolean  ExObjTblLoadActive;
   boolean  ExObjTblLastLoadValid;
   uint16   ExObjTblAttrErrCnt;

   /*
   ** EXOBJ Data
   */

   boolean    EnableDataLoad;
   uint8      Spare;
   uint16     TblIndex;
   uint16     Data1;
   uint16     Data2;
   uint16     Data3;

} OS_PACK _TEMPLATE__HkPkt;

#define _TEMPLATE__TLM_HK_LEN sizeof (_TEMPLATE__HkPkt)

/*
** Exported Data
*/

extern _TEMPLATE__Class  _Template_;

/*
** Exported Functions
*/

/******************************************************************************
** Function: _TEMPLATE__Main
**
*/
void _TEMPLATE__Main(void);

#endif /* __template__ */
