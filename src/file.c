/*
 *	Libraries
 ***********************************************************************/
#include <oriT1/utils.h> /* mkdir_file() */
#include <oriT1/file.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

char FILE_NOT_FOUND[] = "ARQUIVO NAO EXISTE";

/*
 *	Functions
 ***********************************************************************/

/* Cria um arquivo vazio */
bool create_empty(char *fname) {
	/* Cria o diretório para o arquivo se não existir */
	mkdir_file(fname);

	/* Realiza a criação do arquivo */
	FILE *file = fopen(fname, "w");
	if(file != NULL) {
		fclose(file);
		return true;
	} else
		return false;
}

/* Procura por registros vazios */
int find_empty(FILE *file, Record *blockBuffer) {
	/* Seta a posição para o início do arquivo */
	rewind(file);

	Record *worker;
	size_t readBytes;
	int targetRecord;

	/* Lê os registros em blocos */
	while (RECORDS_PERBLOCK == (readBytes = fread(blockBuffer, sizeof(Record), RECORDS_PERBLOCK, file))) {
		worker = blockBuffer;
		/* Percorre os registros do bloco lido atualmente atual */
		for(targetRecord = 0; targetRecord < RECORDS_PERBLOCK; targetRecord++) {
			/* Encontra um espaço vazio e retorna a posição dele no bloco */
			if(worker->removed == true) {
				fseek(file, -BLOCK_SIZE, SEEK_CUR);
				return targetRecord;
			}
			worker++;
		}
	}
	/* Retorna -1 se não houver espaço vazio */
	return (readBytes == 0 ? -1 : -2);
}

/* Insere um registro no arquivo */
void insert(Record newRecord, char *fname) {
	/* Abre o arquivo */
	FILE *file = fopen(fname, "r+b");
	if(file == NULL) {
		puts(FILE_NOT_FOUND);
		return;
	}

	Record block[RECORDS_PERBLOCK];

	int recordIndex = find_empty(file, block);
	/* Retorna a posição de leitura do arquivo e a posição do espaço vazio encontrado */
	printf("ftell: %d, find_empty:%d\n", ftell(file), recordIndex);

	/* Se encontrar um registro removido, grava sobre esse registro. Caso contrário, grava ao fim do arquivo */
	if(recordIndex < 0) {
		/* Cria um novo bloco */
		emptyBlock(block);
		/* Registra na primeira posição */
		block[0] = newRecord;
	} else {
		block[recordIndex] = newRecord;
	}

	/* Faz a gravação do registro */
	fwrite(block, sizeof(Record), RECORDS_PERBLOCK, file);
	fclose(file);
}

void list(char *fname) {
	puts("KEY\tDUMMY\tFOO\tBAR");

	/* Abre o arquivo */
	FILE *file = fopen(fname, "rb");
	if(file == NULL) {
		puts(FILE_NOT_FOUND);
		return;
	}

	Record blockBuffer[RECORDS_PERBLOCK], *worker, *end;
	size_t readBytes;

	/* Percorre os blocos do arquivo */
	while (RECORDS_PERBLOCK == (readBytes = fread(blockBuffer, sizeof(Record), RECORDS_PERBLOCK, file))) {
		end = &blockBuffer[RECORDS_PERBLOCK];
		/* Percorre os registros de cada bloco */
		for(worker = blockBuffer; worker < end; worker++) {
			/* Exibe os registros com exceção dos removidos */
			if(worker->removed == true) {
				puts("[REM]\t---\t---\t---");
			} else {
				printf("%s\t%s\t%s\t%s\n", worker->key, worker->dummy, worker->foo, worker->bar);
			}
		}
	}

	/* Checa se ocorreu tudo bem durante a leitura */
	if(readBytes != 0)
		printf("BAD BLOCK AT EOF! %d\n", readBytes);

	fclose(file);
}

/* Busca um registro */
int find_entry(char *key, FILE *file, Record *blockBuffer) {
	/* Coloca a posição no início do arquivo */
	rewind(file);

	Record *worker;
	size_t readBytes;
	int targetRecord;
	/* Realiza a leitura do arquivo */
	while (RECORDS_PERBLOCK == (readBytes = fread(blockBuffer, sizeof(Record), RECORDS_PERBLOCK, file))) {
		worker = blockBuffer;
		for(targetRecord = 0; targetRecord < RECORDS_PERBLOCK; targetRecord++) {
			/* Retorna a posição do registro se ele nao estiver removido */
			if(worker->removed != true && strcmp(worker->key, key) == 0) {
				fseek(file, -BLOCK_SIZE, SEEK_CUR);
				return targetRecord;
			}
			worker++;
		}
	}

	return (readBytes == 0 ? -1 : -2);
}

/* Função de search.c, realiza a busca de um registro usando find_entry() */
void search(char *fname, char *key) {

	/* Abre o arquivo */
	FILE *file = fopen(fname, "rb");
	if(file == NULL) {
		puts(FILE_NOT_FOUND);
		return;
	}

	Record block[RECORDS_PERBLOCK];
	int recordIndex = find_entry(key, file, block); /* Chama find_entry() */
	printf("ftell: %d, find_entry:%d\n", ftell(file), recordIndex);

	/* Exibe o registro se ele for encontrado */
	if (recordIndex < 0)
		puts("Registro nao encontrado");
	else {
		puts("KEY\tDUMMY\tFOO\tBAR");
		Record *worker = &block[recordIndex];
		printf("%s\t%s\t%s\t%s\n", worker->key, worker->dummy, worker->foo, worker->bar);
	}
}

/* Função que remove os registros */
void remove_ (char *fname, char *key) {
	/* Abre o arquivo */
	FILE *file = fopen(fname, "r+b");
	if (file == NULL) {
		puts(FILE_NOT_FOUND);
		return;
	}

	/* Busca pelo registro a ser removido */
	Record block[RECORDS_PERBLOCK];
	int recordIndex = find_entry(key, file, block);

	/* Se encontrar, marca o registro como removido */
	if (recordIndex < 0)
		return;
	else {
		puts("Removendo registro:");
		Record *worker = &block[recordIndex];
		printf("%s\t%s\t%s\t%s\n", worker->key, worker->dummy, worker->foo, worker->bar);
		worker->removed = true;
		fwrite(block, sizeof(Record), RECORDS_PERBLOCK, file);
	}
}

/* Função que compacta o arquivo */
void vacuum(char *fname) {
	Record output[RECORDS_PERBLOCK],
		input[RECORDS_PERBLOCK],
		*inputEnd = &input[RECORDS_PERBLOCK],
		*outputEnd = &output[RECORDS_PERBLOCK],
		*workIn, *workOut = output;

	/* Cria um bloco vazio */
	emptyBlock(output);
	size_t writtenBlocks = 0;

	/* Estou usando apenas uma stream, então nunca interrompa esse processo! */
	FILE *file = fopen(fname, "r+b");
	if(file == NULL) {
		puts(FILE_NOT_FOUND);
		return;
	}

	size_t traveler, readBytes;
	/* Percorre o bloco */
	while (RECORDS_PERBLOCK == (readBytes = fread(input, sizeof(Record), RECORDS_PERBLOCK, file))) {
		for (workIn = input; workIn < inputEnd; workIn++) {
			if(workIn->removed != true) {
				/* Insere os registros existentes no bloco auxiliar */
				memcpy(workOut, workIn, sizeof(Record));
				workOut++;
				if(workOut >= outputEnd) {
					/* Se workOut chegar ao máximo de registros gravados, obtém a posição atual de leitura */
					traveler = ftell(file);

					/* Reposiciona a leitura do arquivo para o começo do bloco */
					fseek(file, BLOCK_SIZE*writtenBlocks, SEEK_SET);
					/* Escreve o bloco sem espaços vazios no arquivo */
					fwrite(output, sizeof(Record), RECORDS_PERBLOCK, file);
					writtenBlocks++;
					workOut = output;
					/* Limpa o workOut */
					emptyBlock(workOut);
					/* Volta para a posição de leitura do arquivo */
					fseek(file, traveler, SEEK_SET);
				}
			}
		}
	}

	/* Posiciona a leitura para o final do arquivo */
	fseek(file, BLOCK_SIZE*writtenBlocks, SEEK_SET);

	/* Se a workOut for diferente de output, grava output ao fim do arquivo */
	if(workOut != output)
		fwrite(output, sizeof(Record), RECORDS_PERBLOCK, file);

	/* Trunca o arquivo para o tamanho exato utilizado */
	ftruncate(fileno(file), ftello(file));
}
