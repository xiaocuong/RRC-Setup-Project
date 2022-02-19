/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "RRCMessageModule"
 * 	found in "RRCMessage.asn1"
 */

#ifndef	_RRCMessage_H_
#define	_RRCMessage_H_


#include <asn_application.h>

/* Including external dependencies */
#include "ID.h"
#include <BIT_STRING.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* RRCMessage */
typedef struct RRCMessage {
	ID_t	 messid;
	BIT_STRING_t	 data;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} RRCMessage_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_RRCMessage;

#ifdef __cplusplus
}
#endif

#endif	/* _RRCMessage_H_ */
#include <asn_internal.h>
