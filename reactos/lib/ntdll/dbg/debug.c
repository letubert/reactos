/* $Id: debug.c,v 1.5 2002/09/07 15:12:39 chorns Exp $
 *
 * COPYRIGHT:       See COPYING in the top level directory
 * PROJECT:         ReactOS kernel
 * FILE:            lib/ntdll/dbg/debug.c
 * PURPOSE:         User mode debugger support functions
 * PROGRAMMER:      Eric Kohl
 * UPDATE HISTORY:
 *                  14/04/2000 Created
 */

/* INCLUDES *****************************************************************/

#define NTOS_USER_MODE
#include <ntos.h>

#define NDEBUG
#include <debug.h>

/* FUNCTIONS *****************************************************************/

static HANDLE DbgSsApiPort = NULL;
static HANDLE DbgSsReplyPort = NULL;


typedef struct _LPC_DBGSS_MESSAGE
{
	LPC_MESSAGE Header;
	ULONG Unknown1;
	ULONG Unknown2;
	ULONG Unknown3;
	ULONG Unknown4;
} LPC_DBGSS_MESSAGE, *PLPC_DBGSS_MESSAGE;


/* FUNCTIONS *****************************************************************/

VOID STDCALL
DbgSsServerThread(PVOID Unused)
{
	LPC_DBGSS_MESSAGE Message;
	NTSTATUS Status;

	for (;;)
	{
		Status = NtReplyWaitReceivePort (DbgSsApiPort,
		                                 NULL,
		                                 NULL,
		                                 (PLPC_MESSAGE)&Message);
		if (!NT_SUCCESS(Status))
		{
			DbgPrint ("DbgSs: NtReplyWaitReceivePort failed - Status == %lx\n",
			          Status);

			DbgBreakPoint ();
		}
		else
		{
			/* FIXME: missing code!! */

		}
	}
}


NTSTATUS STDCALL
DbgSsHandleKmApiMsg(ULONG Unknown1,
		    HANDLE EventHandle)
{
  return STATUS_NOT_IMPLEMENTED;
}


NTSTATUS STDCALL
DbgSsInitialize(HANDLE ReplyPort,
		ULONG Unknown1,
		ULONG Unknown2,
		ULONG Unknown3)
{
	SECURITY_QUALITY_OF_SERVICE Qos;
	UNICODE_STRING PortName = UNICODE_STRING_INITIALIZER(L"\\DbgSsApiPort");
	NTSTATUS Status;

	Qos.Length = sizeof(SECURITY_QUALITY_OF_SERVICE);
	Qos.ImpersonationLevel = SecurityIdentification;
	Qos.ContextTrackingMode = SECURITY_DYNAMIC_TRACKING;
	Qos.EffectiveOnly = TRUE;

	Status = NtConnectPort (&DbgSsApiPort,
	                        &PortName,
	                        &Qos,
	                        NULL,
	                        NULL,
	                        NULL,
	                        NULL,
	                        NULL);
	if (!NT_SUCCESS(Status))
		return Status;

	DbgSsReplyPort = ReplyPort;
//	UnknownData1 = Unknown1;
//	UnknownData2 = Unknown2;
//	UnknownData3 = Unknown3;

	Status = RtlCreateUserThread (NtCurrentProcess (),
	                              NULL,
	                              FALSE,
	                              0,
	                              NULL,
	                              NULL,
	                              (PTHREAD_START_ROUTINE)DbgSsServerThread,
	                              NULL,
	                              NULL,
	                              NULL);

	return Status;
}


NTSTATUS STDCALL
DbgUiConnectToDbg(VOID)
{
	SECURITY_QUALITY_OF_SERVICE Qos;
	UNICODE_STRING PortName = UNICODE_STRING_INITIALIZER(L"\\DbgUiApiPort");
	NTSTATUS Status;
	PTEB Teb;
	ULONG InfoSize;

	Teb = NtCurrentTeb ();

	Qos.Length = sizeof(SECURITY_QUALITY_OF_SERVICE);
	Qos.ImpersonationLevel = SecurityIdentification;
	Qos.ContextTrackingMode = SECURITY_DYNAMIC_TRACKING;
	Qos.EffectiveOnly = TRUE;

	InfoSize = sizeof(ULONG);

	Status = NtConnectPort (&Teb->DbgSsReserved[1],
	                        &PortName,
	                        &Qos,
	                        NULL,
	                        NULL,
	                        NULL,
	                        &Teb->DbgSsReserved[0],
	                        &InfoSize);
	if (!NT_SUCCESS(Status))
	{
		Teb->DbgSsReserved[1] = NULL;
		return Status;
	}

	NtRegisterThreadTerminatePort(Teb->DbgSsReserved[1]);

	return Status;
}


NTSTATUS STDCALL
DbgUiContinue(PCLIENT_ID ClientId,
	      ULONG ContinueStatus)
{
  return STATUS_NOT_IMPLEMENTED;
}


NTSTATUS STDCALL
DbgUiWaitStateChange(ULONG Unknown1,
		     ULONG Unknown2)
{
  return STATUS_NOT_IMPLEMENTED;
}

/* EOF */
