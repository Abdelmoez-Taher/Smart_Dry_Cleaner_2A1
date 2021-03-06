--------------------------------------------------------
--  Fichier cr?? - lundi-mars-28-2022   
--------------------------------------------------------
DROP TABLE "SYSTEM"."COMMANDES";
DROP TABLE "SYSTEM"."CLIENT";
DROP TABLE "SYSTEM"."COMPTE";
DROP TABLE "SYSTEM"."MATERIEL";
DROP TABLE "SYSTEM"."PERSONNEL";
DROP TABLE "SYSTEM"."PRODUIT";
--------------------------------------------------------
--  DDL for Table COMMANDES
--------------------------------------------------------

  CREATE TABLE "SYSTEM"."COMMANDES" 
   (	"ID" NUMBER, 
	"DATEDEPOT" DATE, 
	"DATERECUPERATION" DATE, 
	"NBRARTICLES" NUMBER, 
	"ETAT" VARCHAR2(50 BYTE), 
	"PRIX" NUMBER, 
	"CIN" NUMBER, 
	"ID_EMPLOYE" NUMBER
   ) PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "SYSTEM" ;
--------------------------------------------------------
--  DDL for Table CLIENT
--------------------------------------------------------

  CREATE TABLE "SYSTEM"."CLIENT" 
   (	"CIN" NUMBER, 
	"NOM" VARCHAR2(255 BYTE), 
	"PRENOM" VARCHAR2(255 BYTE), 
	"NUM_TELEPHONE" NUMBER, 
	"EMAIL" VARCHAR2(255 BYTE)
   ) PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "SYSTEM" ;
--------------------------------------------------------
--  DDL for Table COMPTE
--------------------------------------------------------

  CREATE TABLE "SYSTEM"."COMPTE" 
   (	"MOT_DE_PASSE" VARCHAR2(255 BYTE), 
	"NOM_UTULISATEUR" VARCHAR2(255 BYTE)
   ) PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "SYSTEM" ;
--------------------------------------------------------
--  DDL for Table MATERIEL
--------------------------------------------------------

  CREATE TABLE "SYSTEM"."MATERIEL" 
   (	"N_SERIE" NUMBER, 
	"ID" NUMBER, 
	"MARQUE" VARCHAR2(255 BYTE)
   ) PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "SYSTEM" ;
--------------------------------------------------------
--  DDL for Table PERSONNEL
--------------------------------------------------------

  CREATE TABLE "SYSTEM"."PERSONNEL" 
   (	"CIN" VARCHAR2(255 BYTE), 
	"NOM" VARCHAR2(255 BYTE), 
	"PRENOM" VARCHAR2(255 BYTE), 
	"DATE_NAISSANCE" VARCHAR2(255 BYTE), 
	"ADRESSE" VARCHAR2(255 BYTE), 
	"NUM_TEL" VARCHAR2(255 BYTE)
   ) PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "SYSTEM" ;
--------------------------------------------------------
--  DDL for Table PRODUIT
--------------------------------------------------------

  CREATE TABLE "SYSTEM"."PRODUIT" 
   (	"ID" NUMBER, 
	"NOM" VARCHAR2(255 BYTE), 
	"PRIX" FLOAT(126), 
	"DATEE" VARCHAR2(255 BYTE), 
	"QTE" NUMBER
   ) PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "SYSTEM" ;
REM INSERTING into SYSTEM.COMMANDES
SET DEFINE OFF;
REM INSERTING into SYSTEM.CLIENT
SET DEFINE OFF;
REM INSERTING into SYSTEM.COMPTE
SET DEFINE OFF;
REM INSERTING into SYSTEM.MATERIEL
SET DEFINE OFF;
REM INSERTING into SYSTEM.PERSONNEL
SET DEFINE OFF;
Insert into SYSTEM.PERSONNEL (CIN,NOM,PRENOM,DATE_NAISSANCE,ADRESSE,NUM_TEL) values ('29301','HAMZA','RAHMOUNI','03/01/2000','siliana','90530419');
Insert into SYSTEM.PERSONNEL (CIN,NOM,PRENOM,DATE_NAISSANCE,ADRESSE,NUM_TEL) values ('12335888','tass','hajouja','07/01/2001','fransa','51802983');
Insert into SYSTEM.PERSONNEL (CIN,NOM,PRENOM,DATE_NAISSANCE,ADRESSE,NUM_TEL) values ('12335888','tass','hajouja','07/01/2001','fransa','51802983');
Insert into SYSTEM.PERSONNEL (CIN,NOM,PRENOM,DATE_NAISSANCE,ADRESSE,NUM_TEL) values ('16489821','ti','hj','07/01/2001','fransa','85628452');
Insert into SYSTEM.PERSONNEL (CIN,NOM,PRENOM,DATE_NAISSANCE,ADRESSE,NUM_TEL) values ('42544444','hamza','hamrouni','07/01/1999','amesterdam','86258526');
Insert into SYSTEM.PERSONNEL (CIN,NOM,PRENOM,DATE_NAISSANCE,ADRESSE,NUM_TEL) values ('42544444','hamza','hamrouni','07/01/2003','86258526','55555555');
Insert into SYSTEM.PERSONNEL (CIN,NOM,PRENOM,DATE_NAISSANCE,ADRESSE,NUM_TEL) values ('42544444','hamza','hamrouni','01/08/2003','86258526','55555555');
REM INSERTING into SYSTEM.PRODUIT
SET DEFINE OFF;
