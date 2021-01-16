#include "../src/structs.c"
void Etapas(int *n, char *nomeProva);                                                                                    //função que retira os valores no começo do ficheiro de tempos.txt e guarda em duas posições do vetor n, sendo n[0]<-nEtapas,n[1]<-nPilotos
void loadTempos(TEMPOS *etapa, char *nomeProva);                                                                         //carregamento das informações do ficheiro tempos.txt para uma estrutura que guarda os tempos, saltando os valores iniciais a frente
void loadDistancias(DISTANCIAS *distancias, char *nomeProva);                                                            //carregamento das informações do distancias.txt para o struck DISTANCIAS
void loadPilotos(PILOTO *piloto, char *nomeProva);                                                                       //carregamento das informações ds pilotos.txt para o struct PILoTOS
void loadProva(PROVA *prova, TEMPOS *tempos, PILOTO *piloto, int n, int nPilotos, int nEtapa);                           //carregamenteo das informações dos vários structs para um struct final contento informação da prova por completo
int nPilotosCount(char *nomeProva);                                                                                      //contagem de pilotos contidos no ficheiro pilotos.txt
void verificaProva(TEMPOS *tempos, int n, int *aprovados, int nEtapas);                                                  //verificação de quantos pilotos têm prova valida
void ordenaTemposDesc(PROVA *prova, int nPilotos, int aprovados);                                                        //ordenção e amostra dos tempos por ordem descendente
void medTemposEtapa(TEMPOS *tempos, ETAPAS *etapas, int n, int *aprovados, int *medTempos, int nAprovados, int nEtapas); //media de tempos por etapa
void extremos(PROVA *prova, int nPilotos, int *tempoExtremos);                                                           //Amostra do piloto mais rapido e mais lento
void menorTempo(TEMPOS *tempos, ETAPAS *etapas, int nTotal, int maior, int nEtapas);                                     //Amostra do menor tempo possivel para realizar a prova
void velocidadesMedias(DISTANCIAS *distancias, ETAPAS *etapas, int nEtapas, int *medTempos);                             //Amostra das velocidades medias da prova
void loadTudo(char *nomeProva);
void menu(TEMPOS *tempos, PILOTO *pilotos, DISTANCIAS *distancias, PROVA *prova, ETAPAS *etapas, int nTotal, int nPilotos, int nEtapas, int aprovados, char *nomeProva); //Menu principal do programa
