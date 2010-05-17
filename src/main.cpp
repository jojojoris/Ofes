/*
 * main.cpp
 *
 *  Created on: 13 mei 2010
 *      Author: joris
 */

#include <math/Matrix4.h>
#include <sqlite3/sqlite3.h>

#ifdef PSP
#include <pspkernel.h>
#include <pspdebug.h>
PSP_MODULE_INFO("Ofes_mod", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);
PSP_HEAP_SIZE_MAX();

#define printf pspDebugScreenPrintf
#endif

int main() {
	sqlite3 *db;
	int rc;

#ifdef PSP
	pspDebugScreenInit();
#endif

	printf("Start sqlite3\n");
	rc = sqlite3_open("database.db",&db);

	if(rc){
		printf("Succeed\n");
		printf("Adding some data:\n");
		sqlite3_exec(db,"CREATE TABLE Persons(P_Id int,LastName varchar(255),FirstName varchar(255),Address varchar(255),City varchar(255))",NULL,NULL,NULL);
		sqlite3_exec(db,"INSERT INTO Persons VALUES (4,'Nilsen', 'Johan', 'Bakken 2', 'Stavanger')",NULL,NULL,NULL);
		printf("done\n");
		printf("Unloading Database: ");
		sqlite3_close(db);
		printf("done\n");
	}

	return 0;
}
