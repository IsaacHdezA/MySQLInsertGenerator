/*
 * Desarrollado por: Aldo Isaac Hernández Antonio.
 * Fecha de creación: 06/05/2021.
 * Descripción: Programa que genera un archivo .txt con las sentencias INSERT en MySQL proporcionando un archivo .csv con los datos a introducir a la
 * 		base de datos.
 */

#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

unsigned int countRows( FILE * );

int main( void ) {

	char inputFile[255];
	FILE *archivoInserts;

	cout << "Introduce el nombre del archivo donde tengas la información a almacenar en la base de datos: ";
	cin.getline( inputFile, 256 );

	archivoInserts = fopen( inputFile, "r" );
	if( archivoInserts ) {

		char auxStr[999], *token;
		char *database, *table;

		// Obtenemos del archivo el primer renglón (contiene el nombre de la BD y el nombre de la tabla).
		strcpy( auxStr, fgets( auxStr, 999, archivoInserts ) );
		cout << auxStr << endl;

		// Copiamos el nombre de la base de datos en el string correspondiente.
		token = strtok( auxStr, ";" );
		database = new char[strlen(token) + 1];
		strcpy( database, token );

		// Copiamos el nombre de la tabla en el string correspondiente.
		token = strtok( NULL, "\n" );
		table = new char[strlen(token) + 1];
		strcpy( table, token );

		// Obtenemos el renglón con los atributos de la tabla.
		strcpy( auxStr, fgets( auxStr, 999, archivoInserts ) );
		cout << auxStr << endl;

		// Contamos los atributos para crear un arreglo.
		int i = 0, columnCounter = 0;
		while( auxStr[i] != '\0' ) {
			while( auxStr[i] == ';' ) i++;
			
			if( auxStr[i] != '\0' ) columnCounter++;
			else break;

			while( auxStr[i] != ';' && auxStr[i] != 0 ) i++;
		}

		// Creamos un arreglo de strings (estilo C) para almacenar el nombre de los atributos.
		char **attributes = new char*[columnCounter];

		// Obtenemos el primer atributo y lo copiamos en la primera posición.
		token = strtok( auxStr, ";" );
		attributes[0] = new char[strlen(token)+1];
		strcpy( attributes[0], token );

		// Copiamos los demás atributos al arreglo.
		for( int i = 1; i < columnCounter; i++ ) {
			token = strtok( NULL, ";" );
			attributes[i] = new char[strlen(token)+1];
			strcpy( attributes[i], token );
		}

		cout << "Los atributos de la tabla son:\n";
		for( int i = 0; i < columnCounter; i++ ) cout << '\t' << attributes[i] << '\n';

		FILE *outputFile;

		fclose( archivoInserts );
		delete [] database;
		delete [] table;

		for( int i = 0; i < columnCounter; i++ ) delete[] attributes[i];
		delete [] attributes;
	} else {
		cout << "Hubo un error." << endl;
	}

	return 0;
}

unsigned int countRows( FILE *file ) {
	unsigned int rows = 0;
	char auxStr[999];
	while( fgets( auxStr, 999, file ) && auxStr[0] != '\n' ) rows++;
	rewind( file );

	return rows;
}
