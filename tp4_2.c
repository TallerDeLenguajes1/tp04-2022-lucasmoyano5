#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<unistd.h> 

struct{
        int tareaID;
        char *descripcion;
        int duracion;
        
}typedef tarea;

void cargarTareas(tarea **TAREAS,int cantidad_tareas);
void listarTareas(tarea **TAREAS,tarea **TAREAS_REALIZADAS,int cantidad_tareas);       
void mostrarTareasRealizadasPendientes(tarea **TAREAS,tarea **TAREAS_REALIZADAS,int cantidad_tareas);
tarea *buscarTareaId(tarea **TAREAS,tarea **TAREAS_REALIZADAS,int cantidad_tareas);
tarea *buscarTareaPalabra(tarea **TAREAS,tarea **TAREAS_REALIZADAS,int cantidad_tareas);
 
int main(){
           
           int cantidad_tareas;
           
           tarea **TAREAS;
           tarea **TAREAS_REALIZADAS;
           tarea *TAREABUSCADAID;
           tarea *TAREABUSCADAPALABRA;
  
  
           printf("Ingrese la cantidad de tareas: ");
           scanf("%d",&cantidad_tareas);
           fflush(stdin);
            
           TAREAS = (tarea**)malloc(sizeof(tarea*)*cantidad_tareas);
           TAREAS_REALIZADAS = (tarea**)malloc(sizeof(tarea*)*cantidad_tareas);
           
           
           cargarTareas(TAREAS,cantidad_tareas);
           listarTareas(TAREAS,TAREAS_REALIZADAS,cantidad_tareas);       
           mostrarTareasRealizadasPendientes(TAREAS,TAREAS_REALIZADAS,cantidad_tareas);
           
           TAREABUSCADAID = buscarTareaId(TAREAS,TAREAS_REALIZADAS,cantidad_tareas);
  
           if(TAREABUSCADAID != NULL)
           {
                printf("\nTarea encontrada por id\n");
                printf("-------------------------\n");
                
  		        printf("TareaID: %d\n",TAREABUSCADAID->tareaID);
  		        printf("Descripcion: %s\n",TAREABUSCADAID->descripcion);
  		        printf("Duracion: %d\n\n",TAREABUSCADAID->duracion);
           }
           else
           {
		        printf("No se encontro coincidencias\n");
           }
           
           TAREABUSCADAPALABRA = buscarTareaPalabra(TAREAS,TAREAS_REALIZADAS,cantidad_tareas);
  
           if(TAREABUSCADAPALABRA != NULL)
           {
                printf("\nTarea encontrada por palabra\n");
                printf("------------------------------\n");
                
  		        printf("TareaID: %d\n",TAREABUSCADAPALABRA->tareaID);
  		        printf("Descripcion: %s\n",TAREABUSCADAPALABRA->descripcion);
  		        printf("Duracion: %d\n\n",TAREABUSCADAPALABRA->duracion);
           }
           else
           {
		        printf("No se encontro coincidencias\n");
           }
           
           
         printf("\n\n");
  return 0;
}

void cargarTareas(tarea **TAREAS,int cantidad_tareas){

         int id=1;
         
         char *buff;
         buff=(char *)malloc(100*sizeof(char));      	          
         
         srand(getpid()); 
         
         for(int i=0;i<cantidad_tareas;i++)
         { 
		     TAREAS[i] = (tarea*)malloc(sizeof(tarea));
             
             TAREAS[i]->tareaID=id;
             
             printf("\nIngrese la descripcion de la tarea %d): ",id);
             gets(buff);
             fflush(stdin);

             TAREAS[i]->descripcion = (char *)malloc((strlen(buff)+1)*sizeof(char));
             strcpy(TAREAS[i]->descripcion,buff);
             
             TAREAS[i]->duracion = 10+rand()%90;
			 
			 id++;
		 }
		 free(buff); 
}
 
void listarTareas(tarea **TAREAS,tarea **TAREAS_REALIZADAS,int cantidad_tareas){       
         
         int num=1;
         char respuesta;
          	     
         for(int i=0;i<cantidad_tareas;i++)
         {
             printf("\n\nTarea %d \n",num); 	     
             printf("Descripcion: %s\n",(*(TAREAS+i))->descripcion); 	     
             printf("Duracion: %d\n",(*(TAREAS+i))->duracion); 	     
            
             printf("La tarea (%d) fue realizada? (si: s / no: n): ",num); 	     
             respuesta = getchar();
             fflush(stdin);
         

             if(respuesta=='s')
             {
			       TAREAS_REALIZADAS[i] = (tarea*)malloc(sizeof(tarea));
			       TAREAS_REALIZADAS[i]->tareaID = TAREAS[i]->tareaID;
			     
			       TAREAS_REALIZADAS[i]->descripcion = (char *)malloc((strlen(TAREAS[i]->descripcion)+1)*sizeof(char));
                   strcpy(TAREAS_REALIZADAS[i]->descripcion,TAREAS[i]->descripcion);
		    
		           TAREAS_REALIZADAS[i]->duracion = TAREAS[i]->duracion;
		         
		           TAREAS[i]=NULL;
		     }
		     else
		     {
			      TAREAS_REALIZADAS[i]=NULL;
			 }
		   
		     num++; 
	     } 
	     
}       
 
void mostrarTareasRealizadasPendientes(tarea **TAREAS,tarea **TAREAS_REALIZADAS,int cantidad_tareas){ 
 
		  
         printf("\n\nTareas Pendientes\n");
         printf("-----------------\n\n");
         
         for(int i=0;i<cantidad_tareas;i++) 
         { 
		     if(TAREAS[i] != NULL)
             {     
  		        printf("TareaID: %d\n",TAREAS[i]->tareaID);
  		        printf("Descripcion: %s\n",TAREAS[i]->descripcion);
  		        printf("Duracion: %d\n\n",TAREAS[i]->duracion);
  		     }
		  
		 }
         
         
         printf("\n\nTareas Realizadas\n");
         printf("-----------------\n\n");
         
         for(int i=0;i<cantidad_tareas;i++) 
         { 
		       if(TAREAS_REALIZADAS[i] != NULL)
               {     
  		         printf("TareaID: %d\n",TAREAS_REALIZADAS[i]->tareaID);
  		         printf("Descripcion: %s\n",TAREAS_REALIZADAS[i]->descripcion);
  		         printf("Duracion: %d\n\n",TAREAS_REALIZADAS[i]->duracion);
  		       }
  		      
		 }
}

tarea *buscarTareaId(tarea **TAREAS,tarea **TAREAS_REALIZADAS,int cantidad_tareas){

       int id;
       
       printf("\nIngrese el ID para buscar la tarea: ");
       scanf("%d",&id);
       fflush(stdin);
       
       for(int i=0;i<cantidad_tareas;i++)
       {
		   
	       if ( (TAREAS[i]!= NULL) && (TAREAS[i]->tareaID == id) )
	       {
		        return TAREAS[i];
		   }
		   else
		   {
		       if ( (TAREAS_REALIZADAS[i]!= NULL) && (TAREAS_REALIZADAS[i]->tareaID == id) )
		       {
			         return TAREAS_REALIZADAS[i];
			   }     
		   }
		   
	   }
       return NULL;
        
}

tarea *buscarTareaPalabra(tarea **TAREAS,tarea **TAREAS_REALIZADAS,int cantidad_tareas){

       char *palabra = (char *)malloc(20*sizeof(char));

       printf("\nIngrese la palabra para buscar la tarea: ");
       gets(palabra);
       fflush(stdin);

       for(int i=0;i<cantidad_tareas;i++)
       {
		   
	       if( (TAREAS[i]!=NULL) && (strstr(TAREAS[i]->descripcion,palabra)) )
	       {
		        return TAREAS[i];
		   }
		   else
		   {
		       if ( (TAREAS_REALIZADAS[i]!= NULL) && (strstr(TAREAS_REALIZADAS[i]->descripcion,palabra)) )
		       {
			         return TAREAS_REALIZADAS[i];
			   }     
		   }
		   
	   }
       return NULL;

}
