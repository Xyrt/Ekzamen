#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <Windows.h>

#define FILE_PATH "g:\\"
#define EXTENSION ".recipe"
#define BUFFER 128
#define TEXT_SIZE 5000
#define DATA_SIZE 20
#define RATING_SIZE 15

enum Menu
{
	AddRecipe = 1,
	ChekRecipe = 2,
	EditRecipe = 3,
	DeleteRecipe = 4,
	Exit = 0
};

struct RecipesInfo
{
	char data[DATA_SIZE];
	char text[TEXT_SIZE];
	char rating[RATING_SIZE];
};

void createFilePath(char* filePath, char* fileName);
void addRecipeInfo(char* filePath, struct RecipesInfo* recipesInfo);
void chekRecipes(char* filePath, struct RecipesInfo* recipesInfo);
void editRecipe(char* filePath, struct RecipesInfo* recipesInfo);
void deleteRecipe(char* filePath, struct RecipesInfo* recipesInfo);
void setText(char *text, char *variableToSet, int size);

void createFilePath(char* filePath, char* fileName)
{
	printf("Enter recipe create name: ");
	scanf("%s", fileName);

	strcpy(filePath, FILE_PATH);
	strcat(filePath, fileName);
	strcat(filePath, EXTENSION);
}

void setText(char* text, char* variableToSet, int size)
{
	fflush(stdin);

	printf("%s", text);
	fgets(variableToSet, sizeof(char) * size, stdin);
	sscanf(variableToSet, "%[^\n]", variableToSet);
}


void addRecipeInfo(char* filePath, struct RecipesInfo* recipesInfo)
{
	char createDate[DATA_SIZE];
	char recipeText[TEXT_SIZE];
	char recipeRating[RATING_SIZE];

	setText("", createDate, DATA_SIZE);

	setText("Enter recipe create date: ", createDate, DATA_SIZE);
	setText("Enter recipe text: ", recipeText, TEXT_SIZE);
	setText("Enter recipe rating (from 1 to 10): ", recipeRating, RATING_SIZE);

	strcpy(recipesInfo->data, createDate);
	strcpy(recipesInfo->text, recipeText);
	strcpy(recipesInfo->rating, recipeRating);

	FILE* recipe = fopen(filePath, "wb");
	fwrite(recipesInfo, sizeof(struct RecipesInfo), 1, recipe);
	fclose(recipe);
}

void chekRecipes(char* filePath, struct RecipesInfo* recipesInfo)
{
	int fileToOpen = 0;
	int count = 0;
	filePath = NULL;
	filePath = malloc(BUFFER);
	char* chekFiles = malloc(BUFFER);

	WIN32_FIND_DATAA found;
	HANDLE findResult = FindFirstFileA("g:\\*recipe", &found);

	if (findResult == INVALID_HANDLE_VALUE)
	{
		printf("file not found\n");
		return 1;
	}
	do
	{
		printf("%d: %s\n", count + 1, found.cFileName);
		strcpy(chekFiles, found.cFileName);
		count++;
	} while (FindNextFileA(findResult, &found));
	FindClose(findResult);

	strcpy(filePath, FILE_PATH);
	strcat(filePath, found.cFileName);

	do
	{
		printf("Which file you want to see?\n");
		scanf("%i", &fileToOpen);
	} while (fileToOpen > count);

	FILE* recipe = fopen(filePath, "rb");
	fread(recipesInfo, sizeof(struct RecipesInfo), 1, recipe);
	printf("\nData in your file [%s]: %s\nText: %s\nRating: %s\n\n", found.cFileName, recipesInfo->data, recipesInfo->text, recipesInfo->rating);
	fclose(recipe);
}

void editRecipe(char* filePath, struct RecipesInfo* recipesInfo)
{
	int fileToOpen = 0;
	int count = 0;
	filePath = NULL;
	filePath = malloc(BUFFER);
	char* chekFiles = malloc(BUFFER);
	char newRecipeText[TEXT_SIZE];

	WIN32_FIND_DATAA found;
	HANDLE findResult = FindFirstFileA("g:\\*recipe", &found);

	if (findResult == INVALID_HANDLE_VALUE)
	{
		printf("file not found\n");
		return 1;
	}
	do
	{
		printf("%d: %s\n", count + 1, found.cFileName);
		strcpy(chekFiles, found.cFileName);
		count++;
	} while (FindNextFileA(findResult, &found));
	FindClose(findResult);

	strcpy(filePath, FILE_PATH);
	strcat(filePath, found.cFileName);

	FILE* recipe = fopen(filePath, "wb");
	addRecipeInfo(filePath, recipesInfo);
	printf("\nData in your file [%s]: %s\nText: %s\nRating: %s\n\n", found.cFileName, recipesInfo->data, recipesInfo->text, recipesInfo->rating);
	fclose(recipe);
}

void deleteRecipe(char* filePath, struct RecipesInfo* recipesInfo)
{
	int fileToOpen = 0;
	int count = 0;
	filePath = NULL;
	filePath = malloc(BUFFER);
	char* chekFiles = malloc(BUFFER);
	char newRecipeText[TEXT_SIZE];

	WIN32_FIND_DATAA found;
	HANDLE findResult = FindFirstFileA("g:\\*recipe", &found);

	if (findResult == INVALID_HANDLE_VALUE)
	{
		printf("file not found\n");
		return 1;
	}
	do
	{
		printf("%d: %s\n", count + 1, found.cFileName);
		strcpy(chekFiles, found.cFileName);
		count++;
	} while (FindNextFileA(findResult, &found));
	FindClose(findResult);

	strcpy(filePath, FILE_PATH);
	strcat(filePath, found.cFileName);

	FILE* recipe = fopen(filePath, "wb");
	fclose(recipe);
}

int main()
{
	char* filePath = malloc(BUFFER);
	char* fileName = malloc(BUFFER);
	struct RecipesInfo* recipesInfo = malloc(sizeof(struct RecipesInfo));
	enum Menu menu;	

	memset(recipesInfo->data, 0, DATA_SIZE);
	memset(recipesInfo->text, 0, TEXT_SIZE);
	memset(recipesInfo->rating, 0, RATING_SIZE);

	while (true)
	{
		printf("Menu:\n1 - Add recipe\n2 - Chek recipe\n3 - Edit recipe\n4 - Delete recipe\n0 - Exit\nChoose: ");
		scanf("%i", &menu);

		switch (menu)
		{
		case AddRecipe:
			createFilePath(filePath, fileName);
			addRecipeInfo(filePath, recipesInfo);
			break;
		case ChekRecipe:
			chekRecipes(filePath, recipesInfo);
			break;
		case EditRecipe:
			editRecipe(filePath, recipesInfo);
			break;
		case DeleteRecipe:
			deleteRecipe(filePath, recipesInfo);
			break;
		case Exit:
			printf("Good luck\n");
			return 0;
			break;
		default:
			break;
		}
	}

	free(filePath, fileName);
	return 0;
}
