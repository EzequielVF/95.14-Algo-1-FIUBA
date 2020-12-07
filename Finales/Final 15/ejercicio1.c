// a)
int actualizar_stock() {

    FILE* archivo_stock;
    FILE* archivo_quidditch;
    FILE* archivo_nuevo_stock;
    escoba_t escoba_vendida;
    escoba_t escoba_en_stock;
    int contador_escobas_en_stock = 0;

    if ((abrir_archivos(&archivo_stock, &archivo_quidditch, &archivo_nuevo_stock)) == false) {

        fprintf(stderr, "Hubo un error al intentar abrir los archivos\n");
        return -1;
    }

    fread(&escoba_en_stock, sizeof(escoba_t), 1, archivo_stock);
    fread(&escoba_vendida, sizeof(escoba_t), 1, archivo_quidditch);
    
    // Mientras que hayan escobas vendidas 
    while (!feof(archivo_quidditch)) {

        if (escoba_en_stock.id == escoba_vendida.id) {

            fread(&escoba_en_stock, sizeof(escoba_t), 1, archivo_stock);
            fread(&escoba_vendida, sizeof(escoba_t), 1, archivo_quidditch);    
        }

        else if (escoba_vendida.id > escoba_en_stock.id) {

            fwrite(&escoba_en_stock, sizeof(escoba_t), 1, archivo_nuevo_stock);
            fread(&escoba_en_stock, sizeof(escoba_t), 1,archivo_stock);
        } 
		
        else {

            contador_escobas_en_stock++;
            fread(&escoba_vendida, sizeof(escoba_t), 1, archivo_quidditch);
        } 
    }

    while (!feof(archivo_stock)) {

        fwrite(&escoba_en_stock, sizeof(escoba_t), 1, archivo_nuevo_stock);
        fread(&escoba_en_stock, sizeof(escoba_t), 1, archivo_stock);
    }
	
    while (!feof(archivo_quidditch)) {

        contador_escobas_en_stock++;
        fread(&escoba_vendida, sizeof(escoba_t), 1, archivo_quidditch);
    }

    fclose(archivo_stock);
    fclose(archivo_quidditch);
    fclose(archivo_nuevo_stock);

    return contador_escobas_en_stock;
}

// b)

void listar_escobas() {

    FILE* archivo_stock = fopen(ARCHIVO_NUEVO_STOCK, "rb");
    escoba_t escoba_actual;
    escoba_t comparador_escoba;
    int contador_modelos = 0;

    fread(&escoba_actual, sizeof(escoba_t), 1, archivo_stock);
    comparador_escoba = escoba_actual;

    while (!feof(archivo_stock)) {

        printf("Marca: %s\n", escoba_actual.marca);

        // Agrupo por marca
        while(!feof(archivo_stock) && !strcmp(comparador_escoba.marca, escoba_actual.marca)) {

            // Agrupo por modelo
            while (!feof(archivo_stock) && !strcmp(comparador_escoba.marca, escoba_actual.marca)
                     && comparador_escoba.modelo == escoba_actual.modelo) {

                contador_modelos++;
                comparador_escoba = escoba_actual;
                fread(&escoba_actual, sizeof(escoba_t), 1, archivo_stock);
            }

            printf("\nModelo: %i\tCantidad: %i\n", escoba_actual.modelo, contador_modelos);
            contador_modelos = 0;
        }
    }

    fclose(archivo_stock);
}