/*
 * Desarrollado por: Aldo Isaac Hernández Antonio.
 * Fecha de creación: 06/05/2021.
 * Descripción: Programa que genera un archivo .sql con las sentencias INSERT en MySQL proporcionando un archivo .csv con los datos a introducir a la
 * 		base de datos.
 */

#include <iostream>
#include <cstdio>
#include <cstring>
#include <sys/stat.h>

using namespace std;

unsigned int countRows( FILE * );
void formatSQL( char *str );
void trim( char * );

int main( void ) {

	char inputFile[255];
	FILE *archivoInserts;
	int resp = 0;

	// Creamos la carpeta donde se guardarán los archivos.
	mkdir("salida", 0777 );
	cout << "*** ¡Asegúrate de que cada campo esté separado por \';\' y no por comas (\',\')! ***\n";

	do {
		cout << "Introduce el nombre del archivo donde tengas la información a almacenar en la base de datos: ";
		cin.getline( inputFile, 256 );

		archivoInserts = fopen( inputFile, "r" );
		if( archivoInserts ) {

			char auxStr[999], *token, *database, *table, *attributes, *tuple, *outputFileName;
			FILE *outputFile;
			int rows = countRows(archivoInserts) - 2;

			// Copiamos el nombre de la base de datos en el string correspondiente.
			fgets( auxStr, 999, archivoInserts );
			trim(auxStr);
			token = strtok( auxStr, ";" );
			database = new char[strlen(token) + 1];
			strcpy( database, token );

			// Copiamos el nombre de la tabla en el string correspondiente.
			token = strtok( NULL, ";\n" );
			table = new char[strlen(token) + 1];
			strcpy( table, token );

			cout << "Se creará un archivo con " << rows
			     <<" inserciones en la tabla \"" << table
			     << "\" de la base de datos \"" << database << "\"." << endl;

			// Generamos el nombre del archivo.
			outputFileName = new char[ strlen("./salida/")+strlen(table)+strlen("Inserts.sql")+1 ];
			strcpy( outputFileName, "./salida/" );
			strcat( outputFileName, table );
			strcat( outputFileName, "Inserts.sql" );

			// Creamos el archivo de salida.
			outputFile = fopen( outputFileName, "w" );

			// Obtenemos el renglón con los atributos de la tabla.
			fgets( auxStr, 999, archivoInserts );
			formatSQL(auxStr);
			attributes = new char[strlen(auxStr)+1];
			strcpy( attributes, auxStr );

			fprintf( outputFile, "USE %s;\n", database );
			fprintf( outputFile, "INSERT INTO %s.%s(%s)\n\tVALUES", database, table, attributes );
			for( int i = 0; i < rows; i++ ) {
				fgets(auxStr, 999, archivoInserts);
				formatSQL(auxStr);
				if( i+1 < rows ) fprintf( outputFile, "(%s),\n\t      ", auxStr );
				else fprintf( outputFile, "(%s);", auxStr );
			}

			// Liberamos memoria almacenada.
			delete [] database;
			delete [] table;
			delete [] attributes;
			delete [] outputFileName;
			fclose( archivoInserts );
			fclose( outputFile );

		} else cout << "Hubo un error: El archivo no existe o no se pudo abrir." << endl;

		cout << "\n----------------------------------------------------------------------\n"
		     << "¿Desea generar otro archivo? (1. Sí/0. No)\nRespuesta: ";
		cin >> resp; cin.ignore();
		cout << "----------------------------------------------------------------------\n";

	} while( resp );

	return 0;
}

unsigned int countRows( FILE *file ) {
	unsigned int rows = 0;
	char auxStr[999];
	while( fgets( auxStr, 999, file ) && auxStr[0] != '\n' ) rows++;
	rewind( file );

	return rows;
}

void trim( char *str ) {
	int i = 0;
	int size = strlen(str);

	while( str[i] != '\n' ) i++;
	str[i] = '\0';
}

// Cambia cada coincidencia de ";" por ",".
void formatSQL( char *str ) {
	trim( str );
	for( int i = 0; i < strlen( str )-1; i++ ) if( str[i] == ';' ) str[i] = ',';
}
