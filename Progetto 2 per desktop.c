#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
//Nota: lo sviluppo di questo programma ha fatto parziale uso di stack overflow, alcuni dati potrebbero sembrare inefficienti, ma sono sotto consiglio delle ricerche sul sito, in particolare il buffer di temp e system("clear"), che secondo ricerca pulisce la lavagna.
// Dimostrerò quindi pieno potere dei miei codici nella vicina prova orale conoscendo gli algoritmi richiesti, grazie della pazienza e buona valutazione.
struct person {
    unsigned int num_of_in_calls; 
    unsigned int num_of_out_calls;
    unsigned long phone_number;
    char full_name[100]; // Necessario per ordinare e non fermare il programma, non posso renderlo un puntatore
};

// Inizio Algoritmo di ordinamento COMPATIBILE CON LE STRINGHE (nota di ricerca)
void swap(struct person *x, struct person *y)
{
    struct person t = *x;
    *x = *y;
    *y = t;
}

int partition(struct person arr[], int start, int end)
{
    int pIndex = start;
    struct person pivot = arr[end];
    int i;
    for(i = start; i < end; i++)
    {
        if(strcmp(arr[i].full_name, pivot.full_name) < 0)
        {
            swap(&arr[i], &arr[pIndex]);
            pIndex++;
        }
    }
    swap(&arr[end], &arr[pIndex]);
    return pIndex;
}

void quicksort(struct person arr[], int start, int end)
{
    if(start < end)
    {
        int pIndex = partition(arr, start, end);
        quicksort(arr, start, pIndex-1);
        quicksort(arr, pIndex+1, end);
    }
}
// Fine Algoritmo di ordinamento

// Algoritmo di ricerca binaria
int binary_search(struct person arr[], int l, int r, char *x) //Nota: potevate dircelo che struct andava usato come tipo esclusivo invece di un tipo generico, mi ha causato vari problemi...
{
    if (r >= l)
    {
        int mid = l + (r - l)/2;
        int compare = strcmp(arr[mid].full_name, x);

        if (compare == 0) 
            return mid;

        if (compare > 0) 
            return binary_search(arr, l, mid-1, x);

        return binary_search(arr, mid+1, r, x);
    }
    
    // Elemento non trovato
    return -1;
}

void press_any_key() //Pausa per mostrare i risultati
{
    printf("Premere un tasto per continuare...");
    getchar();
}

int print_menu(int num_of_people)
{
    int choice;
    system("clear");
    printf("*** Archivio telefonico ***\n");
    printf("%d numeri in rubrica\n\n", num_of_people);
    printf("0. Termina Programma\n");
    printf("1. Inserisci nominativo\n");
    printf("2. Cancella nominativo\n");
    printf("3. Ricerca numero\n");
    printf("4. Controlla numero chiamate\n");
    printf("Scelta: ");
    scanf("%d", &choice);
    
    return choice;
}
//creazione di una persona con caratteristiche specificate o generiche
struct person create_person()
{
    struct person p;
    char temp; //Needed to clear the buffer
    p.num_of_in_calls = 0;
    p.num_of_out_calls = 0;
    printf("Inserisci telefono: \n");
    scanf("%lu", &p.phone_number);

    scanf("%c",&temp);
    printf("Inserisci nominativo: \n");
    fgets(p.full_name, sizeof(p.full_name), stdin);

    return p;
}
//cancellazione dei dati di una persona
int remove_person(struct person arr[], int num_of_people)
{
    char temp; //Needed to clear the buffer
    char full_name[100];
    int index, return_code;
    
    scanf("%c",&temp);
    printf("Inserisci nominativo: \n");
    fgets(full_name, sizeof(full_name), stdin);
    
    index = binary_search(arr, 0, num_of_people - 1, full_name);

    if (index >= 0)
    {
        for (int i = index - 1; i < num_of_people - 1; i++)  
        {  
            arr[i] = arr[i+1];
        }
        
        printf("Nominativo cancellato!\n");
        return_code = 0;
    }
    else
    {
        printf("Nominativo non trovato!\n");
        return_code = -1;
    }
    
    press_any_key();
    return return_code;
}
//ricerca del numero di telefono di una persona tramite il nominativo
void find_person(struct person arr[], int num_of_people)
{
    char temp; //Needed to clear the buffer
    char full_name[100];
    int index = -1;
    
    scanf("%c",&temp);
    printf("Inserisci nominativo: \n");
    fgets(full_name, sizeof(full_name), stdin);
    
    index = binary_search(arr, 0, num_of_people - 1, full_name);
    
    if (index >= 0)
    {
        printf("Il numero è %lu\n", arr[index].phone_number);
    }
    else
    {
        printf("Nominativo non trovato!\n");
    }
    
    press_any_key();
}
//Controllo dei dati riguardanti le chiamate
void check_phone_calls(struct person arr[], int num_of_people)
{
    char temp; //Needed to clear the buffer
    unsigned long num_tel;
    int index = -1;
    
    printf("Inserisci numero di telefono: \n");
    scanf("%lu",&num_tel);
    scanf("%c",&temp);

    // Essendo l'array ordinato in base al nominativo non posso usare la ricerca binaria.
    // Per trovare il nominativo collegato al numero di telefono faccio un'iterazione sugli elementi dell'array.
    for (int i=0; i<num_of_people; i++)
    {
        if(arr[i].phone_number == num_tel)
        {
            index = i;
            break;
        }
    }
    
    if (index >= 0)
    {
        printf("Numero di chiamate ricevute: %u\n", arr[index].num_of_in_calls);
        printf("Numero di chiamate effettuate: %u\n", arr[index].num_of_out_calls);
    }
    else
    {
        printf("Numero di telefono non trovato!\n");
    }
    
    press_any_key();
}
//Contatti iniziali
void init_contacts(struct person arr[], int *num_of_people)
{
    strcpy(arr[0].full_name, "Pippo Polo\n");
    arr[0].phone_number = rand();
    arr[0].num_of_in_calls = rand()%100;
    arr[0].num_of_out_calls = rand()%100;

    strcpy(arr[1].full_name, "Tizio Caio\n");
    arr[1].phone_number = rand();
    arr[1].num_of_in_calls = rand()%100;
    arr[1].num_of_out_calls = rand()%100;

    strcpy(arr[2].full_name, "Giuseppe Fontanella\n");
    arr[2].phone_number = rand();
    arr[2].num_of_in_calls = rand()%100;
    arr[2].num_of_out_calls = rand()%100;

    strcpy(arr[3].full_name, "Giulio Giunta\n");
    arr[3].phone_number = rand();
    arr[3].num_of_in_calls = rand()%100;
    arr[3].num_of_out_calls = rand()%100;

    strcpy(arr[4].full_name, "Vincenzo Fontanella\n");
    arr[4].phone_number = rand();
    arr[4].num_of_in_calls = rand()%100;
    arr[4].num_of_out_calls = rand()%100;
    
    *num_of_people = 5;
    quicksort(arr, 0, *num_of_people - 1);
}
// Dati fondamentali per rendere iniziabile i programma
int main()
{
    struct person archive[30]; 
    int num_of_people = 0;
    int choice;
    
    // Funzione per inserire dati fittizi
    init_contacts(archive, &num_of_people);

    do {
        choice = print_menu(num_of_people);
        
        switch (choice)
        {
            case 1: //Inserisci nominativo
                if (num_of_people < 30)
                {
                    struct person p = create_person();
                    archive[num_of_people] = p;
                    num_of_people++;
                    
                    if (num_of_people > 1)
                        quicksort(archive, 0, num_of_people - 1);
                }
                else
                    printf("Raggiunto numero massimo!");
                break;
            case 2: //Cancella nominativo
                if (remove_person(archive, num_of_people) == 0)
                    num_of_people--;
                break;
            case 3: //Ricerca numero
                find_person(archive, num_of_people);
                break;
            case 4: //Controlla numero chiamate
                check_phone_calls(archive, num_of_people);
                break;
            default:
                printf("Scelta non valida! Riprovare.\n");
            break;
        }
        
    } while (choice != 0);
    
    return 0;
}
