#include <mysql.h> 
#include <string.h> 
#include <stdlib.h> 
#include <stdio.h>

int main (void)
{
	MYSQL *conn;
	int err;
	MYSQL_RES *result;
	MYSQL_ROW row;
	
	
	//Inizialize connection
	conn = mysql_init(NULL);
	
	if (conn==NULL)
	{
		printf ("Error creating connection: %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	conn = mysql_real_connect (conn, "localhost","root", "mysql",
							   "Game",0, NULL, 0);
	if (conn==NULL)
	{
		printf ("Error inizialiting connection: %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	//Query SQL
	char query[300];
	
	strcpy(query, "SELECT Games.Id AS GameID, Player.Name AS PlayerName FROM Games JOIN PlayerGame ON Games.Id = PlayerGame.Games JOIN Player ON Player.Id = PlayerGame.Player ORDER BY Games.Id;");
	
	err=mysql_query (conn, query);
	if (err!=0)
	{
		printf ("Error while quering data from database %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	result = mysql_store_result (conn);
	
	row = mysql_fetch_row (result);
	
	int last_game_id=-1; //We haven't processed any game yet
	char player1[80]=""; //We make sure they are empty
	char player2[80]="";
	
	if (row == NULL)
		printf ("No data was obtained in the query\n");
	
	else
	{
		while (row !=NULL)
		{
			int game_id= atoi(row[0]); //convert to integer
			
			if (game_id != last_game_id && last_game_id != -1) {
				printf ("Game ID: %d\n Players' names: %s,%s \n", last_game_id, player1, player2);
				strcpy(player1, "");  // We clean the names for the following game
				strcpy(player2, "");
			}
			
			if (strcmp(player1, "") == 0) {
				strcpy(player1, row[1]);
			} 
			else {
				strcpy(player2, row[1]);
			}
			
			last_game_id= game_id;
			
			row = mysql_fetch_row (result);
			
		}
			
		if (last_game_id != -1) {
			printf("Game ID: %d\nPlayers' names: %s, %s\n\n", last_game_id, player1, player2);
		}
			
		
	}
		mysql_close(conn);
		
}

