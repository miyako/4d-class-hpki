#ifndef APDU_H
#define APDU_H

#include "json/json.h"

#include "openssl/bio.h"
#include <openssl/pem.h>
#include <openssl/x509.h>
#include <openssl/asn1.h>

void bytes_to_hex(const uint8_t *pbtData, const size_t szBytes, std::string &hex);
void hex_to_bytes(std::string &hex, std::vector<uint8_t>& buf);
void asn_time_to_iso(ASN1_TIME *asn_time, std::string& str);

#define MY_NUMBER_LENGTH 12
#define APP_AUX_RESPONSE_HEADER_LENGTH 3
#define APDU_RESPONSE_LENGTH 2

#define ID_HPKI "004e0000f781d100"
#define ID_JPKI "000041e0b381a100"

#define NAME_HPKI "HPKI"
#define NAME_JPKI "JPKI"

typedef enum {
    certificate_type_identity  = 0,
    certificate_type_signature = 1
}certificate_type_t;

static const unsigned char DIGEST_INFO[] = {
    0x30, 0x31,
    0x30, 0x0B,
    0x06, 0x09,
    0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x01,
    0x05, 0x00,
    0x04, 0x20,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00
};

const unsigned char APDU_COMPUTE_DIGITAL_SIGNATURE_KEY_JPKI[] = {0x80, 0x2A, 0x00, 0x80,
    0x00,
    0x00, 0x00,
    0x00, 0x00,
        0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00,
    0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00};

#pragma mark JPKI

//公的個人認証AP
#define APDU_SELECT_IDENTITY_AP_JPKI  "D392F000260100000001"
#define APDU_SELECT_CARD_AP_JPKI  "D3921000310001010408"

#define APDU_SELECT_FILE_DF_P2_RFU_JPKI 0x0C


const unsigned char APDU_SELECT_APP_AUX[] =  {0x00, 0xA4, 0x04, 0x0C,
    0x0A,
    0xD3, 0x92, 0x10, 0x00, 0x31, 0x00, 0x01, 0x01, 0x04, 0x08};

#pragma mark APDU

//READ BINARY
const unsigned char APDU_READ_BINARY[] =            {0x00, 0xB0, 0x00, 0x00, 0x00};
const unsigned char APDU_READ_BINARY_GET_LENGTH[] = {0x00, 0xB0, 0x00, 0x00, 0x04};

//VERIFY
#define APDU_VERIFY_PIN_EF_JPKI 0x80
#define APDU_VERIFY_PIN_EF_HPKI 0x88
const unsigned char APDU_VERIFY_PIN[] = {0x00, 0x20, 0x00, 0x00, 0x00};

//SELECT FILE (EF under DF)
#define APDU_SELECT_PIN_EF_HPKI_HI 0x00
#define APDU_SELECT_PIN_EF_HPKI_LO 0x02

#define APDU_SELECT_KEY_EF_HPKI_HI 0x00
#define APDU_SELECT_KEY_EF_HPKI_LO 0x0C

#define APDU_SELECT_CRT_EF_HPKI_HI 0x00
#define APDU_SELECT_CRT_EF_HPKI_LO 0x16

#define APDU_SELECT_BASIC4I_EF_JPKI_HI 0x00
#define APDU_SELECT_BASIC4I_EF_JPKI_LO 0x02

#define APDU_SELECT_MNUMBER_EF_JPKI_HI 0x00
#define APDU_SELECT_MNUMBER_EF_JPKI_LO 0x01

#define APDU_SELECT_CRT_SIGNATURE_EF_JPKI_HI 0x00
#define APDU_SELECT_CRT_SIGNATURE_EF_JPKI_LO 0x01

#define APDU_SELECT_CRT_IDENTITY_EF_JPKI_HI 0x00
#define APDU_SELECT_CRT_IDENTITY_EF_JPKI_LO 0x0A

#define APDU_SELECT_PIN_SIGNATURE_EF_JPKI_HI 0x00
#define APDU_SELECT_PIN_SIGNATURE_EF_JPKI_LO 0x1B

#define APDU_SELECT_KEY_SIGNATURE_EF_JPKI_HI 0x00
#define APDU_SELECT_KEY_SIGNATURE_EF_JPKI_LO 0x1A

#define APDU_SELECT_PIN_IDENTITY_EF_JPKI_HI 0x00
#define APDU_SELECT_PIN_IDENTITY_EF_JPKI_LO 0x18

#define APDU_SELECT_KEY_IDENTITY_EF_JPKI_HI 0x00
#define APDU_SELECT_KEY_IDENTITY_EF_JPKI_LO 0x17

#define APDU_SELECT_PIN_CARD_EF_JPKI_HI 0x00
#define APDU_SELECT_PIN_CARD_EF_JPKI_LO 0x11

const unsigned char APDU_SELECT_EF_UNDER_DF[] = {0x00, 0xA4, 0x02, 0x0C,
    0x02,
    0x00, 0x00};

//SELECT FILE (DF)
const unsigned char APDU_SELECT_FILE_DF[] = {0x00, 0xA4, 0x04, 0x00,
    0x00,
    0x00};

#pragma mark HPKI

#define APDU_SELECT_IDENTITY_AP_HPKI  "E828BD080FA000000391000000000002"
#define APDU_SELECT_SIGNATURE_AP_HPKI "E828BD080FA000000391000000000001"

typedef enum {
    pki_type_j = 0,
    pki_type_h = 1,
    pki_type_unknown = -1
} pki_type_t;

#endif /* APDU_H */
