#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<unistd.h> 

struct Tarea{
        int tareaID;
        char *descripcion;
        int duracion;
        
}typedef Tarea;

struct nodo{ 
        
        Tarea tarea;
        struct nodo* siguiente;
        
}typedef nodo;


nodo *crearListaVacia();

nodo *crearTarea(int id_tarea); 
 
void insertarTarea(nodo** LISTADO_TAREAS, nodo* tarea); 

void eliminarTarea(nodo* LISTADO_TAREAS, int id_tarea); 
 
void cargarTareas(nodo** LISTADO_TAREAS, int cantidad_tareas);
   
void consultarEstadosTareas(nodo** LISTADO_TAREAS_PENDIENTES,nodo** LISTADO_TAREAS_REALIZADAS); 

void mostrarTarea(Tarea tarea);

void mostrarTareas(nodo* LISTADO_TAREAS);   

nodo* buscarTareaPorID(nodo** LISTADO_TAREAS, int id_tarea);

nodo* buscarTareaPorPalabra(nodo** LISTADO_TAREAS, char* palarbra_clave);


int main(){
          
          srand((int) time(NULL));
 
          nodo *LISTADO_TAREAS_PENDIENTES = crearListaVacia(); 
          nodo *LISTADO_TAREAS_REALIZADAS = crearListaVacia(); 
          
          int cantidad_tareas;
          int id_tarea_buscar;
          
          char* buffer;
          char* palabra_clave;
          
          printf("Ingrese la cantidad de tareas: ");
          scanf("%d",&cantidad_tareas);
          fflush(stdin);
          
          cargarTareas(&LISTADO_TAREAS_PENDIENTES,cantidad_tareas);

          consultarEstadosTareas(&LISTADO_TAREAS_PENDIENTES, &LISTADO_TAREAS_REALIZADAS);
          
           printf("\n\nListado de Tareas Realizadas\n");
           printf("--------------------------------\n");
           mostrarTareas(LISTADO_TAREAS_REALIZADAS);

           printf("\n\nListado de Tareas Pendientes\n");    
           printf("--------------------------------\n");
           mostrarTareas(LISTADO_TAREAS_PENDIENTES);

           printf("\nIngrese el id de la tarea que desea buscar: ");
           scanf("%d", &id_tarea_buscar);
           fflush(stdin);

           if(buscarTareaPorID(&LISTADO_TAREAS_PENDIENTES, id_tarea_buscar) ) 
           {
                   mostrarTarea( buscarTareaPorID(&LISTADO_TAREAS_PENDIENTES, id_tarea_buscar)->tarea ); 

           } else if ( buscarTareaPorID(&LISTADO_TAREAS_REALIZADAS, id_tarea_buscar) ) 
                  {
                     mostrarTarea( buscarTareaPorID(&LISTADO_TAREAS_REALIZADAS, id_tarea_buscar)->tarea );
                  } 
                  else 
                  {
                     printf("No se encontro coincidencias\n");
                  }     

           buffer = (char*) malloc( sizeof(char) * 50 );

           printf("\nIngrese la palabra clave de la tarea que desea buscar: ");
           gets(buffer);
   
           palabra_clave = (char*) malloc( sizeof(char) * (strlen(buffer) + 1) );
           strcpy(palabra_clave, buffer);
           free(buffer);
    
    
           printf("\nEl resultado de la busqueda \'%s\' :\n", palabra_clave);
     
          if( buscarTareaPorPalabra(&LISTADO_TAREAS_PENDIENTES, palabra_clave) ) 
          {
              mostrarTarea( buscarTareaPorPalabra(&LISTADO_TAREAS_PENDIENTES, palabra_clave)->tarea );

          } else if( buscarTareaPorPalabra(&LISTADO_TAREAS_REALIZADAS, palabra_clave) ) 
                   {
                        mostrarTarea( buscarTareaPorPalabra(&LISTADO_TAREAS_REALIZADAS, palabra_clave)->tarea );
                   } 
                   else 
                   {
					 printf("No se encontro coincidencias\n");
                   }

  
  
  printf("\n\n");
  return 0;
}


nodo *crearListaVacia(){
     
      return NULL;
}

nodo *crearTarea(int id_tarea){
   
     nodo *nueva_tarea = (nodo*) malloc( sizeof(nodo) );
     char* buff = (char*) malloc( sizeof(char) * 100 );
     
     nueva_tarea->tarea.tareaID = id_tarea+1;
    
     printf("\nIngrese la descripcion de la tarea %d): ",id_tarea+1);
     gets(buff);
     fflush(stdin);

     nueva_tarea->tarea.descripcion = (char*) malloc( sizeof(char) * ( strlen(buff) + 1 ) );
     
     strcpy(nueva_tarea->tarea.descripcion,buff);
    
     nueva_tarea->tarea.duracion = 10 + rand() % 90;

     nueva_tarea->siguiente = NULL;

     return nueva_tarea;
}
 
 void insertarTarea(nodo** LISTADO_TAREAS, nodo* tarea){

     tarea->siguiente = *LISTADO_TAREAS;

    *LISTADO_TAREAS = tarea;
}


void cargarTareas(nodo** LISTADO_TAREAS, int cantidad_tareas){
    
    for(int i=0;i < cantidad_tareas;i++) 
    {
        insertarTarea(LISTADO_TAREAS,crearTarea(i));
    } 

}
 

void mostrarTarea(Tarea tarea){
    
    printf("\nTareaID: %d\n", tarea.tareaID);
    printf("Descripcion: %s\n", tarea.descripcion);
    printf("Duracion: %d\n", tarea.duracion);
} 

 
void mostrarTareas(nodo* LISTADO_TAREAS){

    nodo* tarea_aux = LISTADO_TAREAS;

    while(tarea_aux) 
    {
        mostrarTarea(tarea_aux->tarea);

        tarea_aux = tarea_aux->siguiente;
    }
} 



void eliminarTarea(nodo* LISTADO_TAREAS, int id_tarea){

    nodo* tarea = LISTADO_TAREAS;
    nodo* tarea_anterior = LISTADO_TAREAS;

    while(tarea && tarea->tarea.tareaID != id_tarea) 
    {
        tarea_anterior = tarea;
        tarea = tarea->siguiente;
    }

    if(tarea) 
    {
        tarea_anterior->siguiente = tarea->siguiente;
    } 

}  
 

void consultarEstadosTareas(nodo** LISTADO_TAREAS_PENDIENTES,nodo** LISTADO_TAREAS_REALIZADAS){

    nodo* tarea_aux = *LISTADO_TAREAS_PENDIENTES;

    while(tarea_aux)
    {
        char respuesta; 

        mostrarTarea(tarea_aux->tarea); 
 
        printf("La tarea fue realizada? (si: s / no: n): "); 	     
        respuesta = getchar();
        fflush(stdin);

        if(respuesta == 's') 
        {
            nodo* tarea_realizada_aux = tarea_aux;
            
            tarea_aux = tarea_aux->siguiente;
            
            eliminarTarea(*LISTADO_TAREAS_PENDIENTES, tarea_realizada_aux->tarea.tareaID); 
            
            insertarTarea(LISTADO_TAREAS_REALIZADAS,tarea_realizada_aux);
        } 
        else 
        {
            tarea_aux = tarea_aux->siguiente;
        }
     } 

}
 
nodo* buscarTareaPorID(nodo** LISTADO_TAREAS, int id_tarea){

     nodo* tarea_aux = *LISTADO_TAREAS;

     while(tarea_aux && tarea_aux->tarea.tareaID != id_tarea) 
     {
          tarea_aux = tarea_aux->siguiente;
     }

     return tarea_aux;
}


nodo* buscarTareaPorPalabra(nodo** LISTADO_TAREAS, char* palarbra_clave){

     nodo* tarea_aux = *LISTADO_TAREAS;

     while(tarea_aux && !strstr(tarea_aux->tarea.descripcion, palarbra_clave)) 
     {
        tarea_aux = tarea_aux->siguiente;
     } 

    return tarea_aux;
} 
 
