#include "service.h"
#include "libfinance.h"
#include "accounting_trade_data.h"
#include "service_accounting.h"
#include "cre_function.h"
#include "cre_generator.h"

using std::string;
using std::vector;
using std::shared_ptr;
using boost::property_tree::ptree;
using boost::property_tree::ptree_error;

using namespace std;


    void cre_generator::load_format(const string & formatname)
    {
        if( fname== formatname) 
        {
            return;
        }
        
        fname= formatname;
        list_format.clear();

       
    add_field("CDREGL",STRING,LEFT,' ',5,0,(void*)TypeCRE_SwapParis);  /// Field:1 Position:1
    add_field("DTEMI",STRING,LEFT,' ',8,0,(void*)dateAsof);  /// Field:2 Position:6
    add_field("CTRBAL",STRING,LEFT,' ',1,0,(void*)empty_field);  /// Field:3 Position:14
    add_field("CDANN",STRING,LEFT,' ',1,0,(void*)isReversal);  /// Field:4 Position:15
    add_field("NUMCRE",STRING,RIGHT,'0',6,0,(void*)empty_field);  /// Field:5 Position:16
    add_field("CDLSTR",STRING,LEFT,' ',8,0,(void*)empty_field);  /// Field:6 Position:22
    add_field("IDCRELOG",STRING,LEFT,' ',20,0,(void*)empty_field);  /// Field:7 Position:30
    add_field("INSTRUMT",STRING,LEFT,' ',5,0,(void*)CodeInstrument_RDJ);  /// Field:8 Position:50
    add_field("TYP_SWAP",STRING,LEFT,' ',4,0,(void*)TODO);  /// Field:9 Position:55
    add_field("REF_BO_18A",STRING,RIGHT,' ',18,0,(void*)getBackId);  /// Field:10 Position:59
    add_field("REF_OFO",STRING,RIGHT,' ',18,0,(void*)getFrontId);  /// Field:11 Position:77
    add_field("REFINT_18A",STRING,LEFT,' ',18,0,(void*)TODO);  /// Field:12 Position:95
    add_field("TOP_NOT",STRING,LEFT,' ',5,0,(void*)TODO);  /// Field:13 Position:113
    add_field("NET_FLUX",STRING,LEFT,' ',1,0,(void*)TODO);  /// Field:14 Position:118
    add_field("NET_CONT",STRING,LEFT,' ',1,0,(void*)TODO);  /// Field:15 Position:119
    add_field("CDR_PRI",STRING,LEFT,' ',5,0,(void*)getCDR);  /// Field:16 Position:120
    add_field("TIERS_8A",STRING,LEFT,' ',8,0,(void*)getSIAM);  /// Field:17 Position:125
    add_field("DAT_OPE",STRING,LEFT,' ',8,0,(void*)dateAsof);  /// Field:18 Position:133
    add_field("DAT_VAL",STRING,LEFT,' ',8,0,(void*)getValueDate);  /// Field:19 Position:141
    add_field("DAT-ECH",STRING,LEFT,' ',8,0,(void*)getMatDate);  /// Field:20 Position:149
    add_field("LIBEL_31A",STRING,LEFT,' ',31,0,(void*)TODO);  /// Field:21 Position:157
    add_field("DEV_COURT",STRING,LEFT,' ',3,0,(void*)TODO);  /// Field:22 Position:188
    add_field("MTCOUDEV16",STRING,LEFT,' ',16,0,(void*)TODO);  /// Field:23 Position:191
    add_field("CV_COU_N16",STRING,LEFT,' ',16,0,(void*)TODO);  /// Field:24 Position:207
    add_field("COURTIER",STRING,LEFT,' ',8,0,(void*)TODO);  /// Field:25 Position:223
    add_field("R_DEV_IMP",STRING,LEFT,' ',3,0,(void*)TODO);  /// Field:26 Position:231
    add_field("R_NOM_IDEV",STRING,LEFT,' ',16,0,(void*)TODO);  /// Field:27 Position:234
    add_field("R_NOM_ICV",STRING,LEFT,' ',16,0,(void*)TODO);  /// Field:28 Position:250
    add_field("R_TYPTAUX",STRING,LEFT,' ',1,0,(void*)TODO);  /// Field:29 Position:266
    add_field("R_VAL_TAUX",STRING,LEFT,' ',11,0,(void*)TODO);  /// Field:30 Position:267
    add_field("R_SNS_MTM",STRING,LEFT,' ',1,0,(void*)TODO);  /// Field:31 Position:278
    add_field("R_MTM_DEV",STRING,LEFT,' ',16,0,(void*)TODO);  /// Field:32 Position:279
    add_field("R_MTM_CV",STRING,LEFT,' ',16,0,(void*)TODO);  /// Field:33 Position:295
    add_field("R_SNS_INT",STRING,LEFT,' ',1,0,(void*)TODO);  /// Field:34 Position:311
    add_field("R_DEV_INT",STRING,LEFT,' ',3,0,(void*)TODO);  /// Field:35 Position:312
    add_field("R_INT_DEV",STRING,LEFT,' ',16,0,(void*)TODO);  /// Field:36 Position:315
    add_field("R_INT_CV",STRING,LEFT,' ',16,0,(void*)TODO);  /// Field:37 Position:331
    add_field("R_SNS_SOUL",STRING,LEFT,' ',1,0,(void*)TODO);  /// Field:38 Position:347
    add_field("R_DEV_SOU",STRING,LEFT,' ',3,0,(void*)TODO);  /// Field:39 Position:348
    add_field("R_EFTX_DEV",STRING,LEFT,' ',16,0,(void*)TODO);  /// Field:40 Position:351
    add_field("R_EFTX_CV",STRING,LEFT,' ',16,0,(void*)TODO);  /// Field:41 Position:367
    add_field("R_DATE_REG",STRING,LEFT,' ',8,0,(void*)TODO);  /// Field:42 Position:383
    add_field("R_DEV_REG",STRING,LEFT,' ',3,0,(void*)TODO);  /// Field:43 Position:391
    add_field("RMODREG_4A",STRING,LEFT,' ',4,0,(void*)TODO);  /// Field:44 Position:394
    add_field("R_MNT_REG",STRING,LEFT,' ',16,0,(void*)TODO);  /// Field:45 Position:398
    add_field("R_AGENCE",STRING,LEFT,' ',5,0,(void*)TODO);  /// Field:46 Position:414
    add_field("R_COMPTE",STRING,LEFT,' ',6,0,(void*)TODO);  /// Field:47 Position:419
    add_field("R_CLE_CPTE",STRING,LEFT,' ',1,0,(void*)TODO);  /// Field:48 Position:425
    add_field("R_DOSSIER",STRING,LEFT,' ',3,0,(void*)TODO);  /// Field:49 Position:426
    add_field(" L_DEV_IMP",STRING,LEFT,' ',3,0,(void*)TODO);  /// Field:50 Position:429
    add_field("L_NOM_IDEV",STRING,LEFT,' ',16,0,(void*)TODO);  /// Field:51 Position:432
    add_field("L_NOM_ICV",STRING,LEFT,' ',16,0,(void*)TODO);  /// Field:52 Position:448
    add_field("L_TYPTAUX",STRING,LEFT,' ',1,0,(void*)TODO);  /// Field:53 Position:464
    add_field("L_VAL_TAUX",STRING,LEFT,' ',11,0,(void*)TODO);  /// Field:54 Position:465
    add_field("L_SNS_MTM",STRING,LEFT,' ',1,0,(void*)TODO);  /// Field:55 Position:476
    add_field("L_MTM_DEV",STRING,LEFT,' ',16,0,(void*)TODO);  /// Field:56 Position:477
    add_field("L_MTM_CV",STRING,LEFT,' ',16,0,(void*)TODO);  /// Field:57 Position:493
    add_field("L_SNS_INT",STRING,LEFT,' ',1,0,(void*)TODO);  /// Field:58 Position:509
    add_field("L_DEV_INT",STRING,LEFT,' ',3,0,(void*)TODO);  /// Field:59 Position:510
    add_field("L_INT_DEV",STRING,LEFT,' ',16,0,(void*)TODO);  /// Field:60 Position:513
    add_field("L_INT_CV",STRING,LEFT,' ',16,0,(void*)TODO);  /// Field:61 Position:529
    add_field("L_SNS_SOUL",STRING,LEFT,' ',1,0,(void*)TODO);  /// Field:62 Position:545
    add_field("L_DEV_SOU",STRING,LEFT,' ',3,0,(void*)TODO);  /// Field:63 Position:546
    add_field("L_EFTX_DEV",STRING,LEFT,' ',16,0,(void*)TODO);  /// Field:64 Position:549
    add_field("L_EFTX_CV",STRING,LEFT,' ',16,0,(void*)TODO);  /// Field:65 Position:565
    add_field("L_DATE_REG",STRING,LEFT,' ',8,0,(void*)TODO);  /// Field:66 Position:581
    add_field("L_DEV_REG",STRING,LEFT,' ',3,0,(void*)TODO);  /// Field:67 Position:589
    add_field("LMODREG_4A",STRING,LEFT,' ',4,0,(void*)TODO);  /// Field:68 Position:592
    add_field("L_MNT_REG",STRING,LEFT,' ',16,0,(void*)TODO);  /// Field:69 Position:596
    add_field("L_AGENCE",STRING,LEFT,' ',5,0,(void*)TODO);  /// Field:70 Position:612
    add_field("L_COMPTE",STRING,LEFT,' ',6,0,(void*)TODO);  /// Field:71 Position:617
    add_field("L_CLE_CPTE",STRING,LEFT,' ',1,0,(void*)TODO);  /// Field:72 Position:623
    add_field("L_DOSSIER",STRING,LEFT,' ',3,0,(void*)TODO);  /// Field:73 Position:624
    add_field("TOP_CALYON",STRING,LEFT,' ',1,0,(void*)TODO);  /// Field:74 Position:627
    add_field("R_CPT_CALYON",STRING,LEFT,' ',11,0,(void*)TODO);  /// Field:75 Position:628
    add_field("L_CPT_CALYON",STRING,LEFT,' ',11,0,(void*)TODO);  /// Field:76 Position:639
    add_field("REF_SWIFT20",STRING,LEFT,' ',16,0,(void*)TODO);  /// Field:77 Position:650
    add_field("REF_SWIFT21",STRING,LEFT,' ',16,0,(void*)TODO);  /// Field:78 Position:666
    add_field("COD_TID",STRING,LEFT,' ',11,0,(void*)TODO);  /// Field:79 Position:682
    add_field("SC_POSTING",STRING,LEFT,' ',15,0,(void*)TODO);  /// Field:80 Position:693
    add_field("SC_ACCOUNT",STRING,LEFT,' ',1,0,(void*)TODO);  /// Field:81 Position:708
    add_field("SC_TRADATE",STRING,LEFT,' ',8,0,(void*)TODO);  /// Field:82 Position:709
    add_field("SC_VALDATE",STRING,LEFT,' ',8,0,(void*)TODO);  /// Field:83 Position:717
    add_field("SC_MONTANT",STRING,LEFT,' ',16,0,(void*)TODO);  /// Field:84 Position:725
    add_field("SC_DEV",STRING,LEFT,' ',3,0,(void*)TODO);  /// Field:85 Position:741
    add_field("SC_SENS",STRING,LEFT,' ',1,0,(void*)TODO);  /// Field:86 Position:744
    add_field("SC_CV",STRING,LEFT,' ',16,0,(void*)TODO);  /// Field:87 Position:745
    add_field("SNSMTM",STRING,LEFT,' ',1,0,(void*)TODO);  /// Field:88 Position:761
    add_field("DEV_MT_MTM",STRING,LEFT,' ',3,0,(void*)TODO);  /// Field:89 Position:762
    add_field("MTMTMDEV",STRING,LEFT,' ',16,0,(void*)TODO);  /// Field:90 Position:765
    add_field("CVMTMTM",STRING,LEFT,' ',16,0,(void*)TODO);  /// Field:91 Position:781
    add_field("BRANCHE",STRING,LEFT,' ',1,0,(void*)TODO);  /// Field:92 Position:797
    add_field("DATEOP_8A",STRING,LEFT,' ',8,0,(void*)TODO);  /// Field:93 Position:798
    add_field("CD_SITE",STRING,LEFT,' ',12,0,(void*)TODO);  /// Field:94 Position:806
    add_field("SENS_5",STRING,LEFT,' ',5,0,(void*)TODO);  /// Field:95 Position:818
    add_field("NAT_SJ_5",STRING,LEFT,' ',1,0,(void*)TODO);  /// Field:96 Position:823
    add_field("R_NAT_COMPTE",STRING,LEFT,' ',1,0,(void*)TODO);  /// Field:97 Position:824
    add_field("L_NAT_COMPTE",STRING,LEFT,' ',1,0,(void*)TODO);  /// Field:98 Position:825
    add_field("TOP_ETAL",STRING,LEFT,' ',1,0,(void*)TODO);  /// Field:99 Position:826
    add_field("CTP_RICOS",STRING,LEFT,' ',12,0,(void*)CustRICOS);  /// Field:100 Position:827
    add_field("COURTIER_RICOS",STRING,LEFT,' ',12,0,(void*)TODO);  /// Field:101 Position:839
    add_field("R_SNS_PDC",STRING,LEFT,' ',1,0,(void*)TODO);  /// Field:102 Position:851
    add_field("R_MNT_PDC",STRING,LEFT,' ',18,0,(void*)TODO);  /// Field:103 Position:852
    add_field("R_DEV_PDC",STRING,LEFT,' ',3,0,(void*)TODO);  /// Field:104 Position:870
    add_field("R_CV_PDC",STRING,LEFT,' ',18,0,(void*)TODO);  /// Field:105 Position:873
    add_field("L_SNS_PDC",STRING,LEFT,' ',1,0,(void*)TODO);  /// Field:106 Position:891
    add_field("L_MNT_PDC",STRING,LEFT,' ',18,0,(void*)TODO);  /// Field:107 Position:892
    add_field("L_DEV_PDC",STRING,LEFT,' ',3,0,(void*)TODO);  /// Field:108 Position:910
    add_field("L_CV_PDC",STRING,LEFT,' ',18,0,(void*)TODO);  /// Field:109 Position:913
    add_field("TOP_ALM",STRING,LEFT,' ',1,0,(void*)TODO);  /// Field:110 Position:931
    add_field("C_CLEARING",STRING,LEFT,' ',1,0,(void*)TODO);  /// Field:111 Position:932
    add_field("TH_ENTCODE",STRING,LEFT,' ',5,0,(void*)TODO);  /// Field:112 Position:933
    add_field("KEY_BRANCH",STRING,LEFT,' ',12,0,(void*)TODO);  /// Field:113 Position:938
    add_field("KEY_RC",STRING,LEFT,' ',5,0,(void*)TODO);  /// Field:114 Position:950
    add_field("KEY_EXCPTY",STRING,RIGHT,'0',6,0,(void*)TODO);  /// Field:115 Position:955
    add_field("TH_ENTCURR",STRING,LEFT,' ',3,0,(void*)TODO);  /// Field:116 Position:961
    add_field("L_ACCOUNT_DDA",STRING,LEFT,' ',14,0,(void*)TODO);  /// Field:117 Position:964
    add_field("R_ACCOUNT_DDA",STRING,LEFT,' ',14,0,(void*)TODO);  /// Field:118 Position:978
    add_field("CLEARED",STRING,LEFT,' ',1,0,(void*)TODO);  /// Field:119 Position:992
    add_field("CLEARING_HOUSE",STRING,LEFT,' ',15,0,(void*)TODO);  /// Field:120 Position:993
    add_field("Ref_Montage",STRING,LEFT,' ',20,0,(void*)TODO);  /// Field:121 Position:1008
    add_field("Code Isin",STRING,LEFT,' ',20,0,(void*)TODO);  /// Field:122 Position:1028
    add_field("FILLER_99A",STRING,LEFT,' ',59,0,(void*)TODO);  /// Field:123 Position:1048
};



