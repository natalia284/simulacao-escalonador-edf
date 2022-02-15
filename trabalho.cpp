/*
  Esse exemplo simula um sistema EDF com 3 Tasks. O sistema 
  pertence a um super computador conhecido como Enma Core. 
  
  As Tasks foram criadas para processar os dados de um novo hardware 
  adicionado a sua estrutura.  
    -
            | Task 1 | Task 2 | Task 3 |
    a_i     |   0    |   0    |  200   | 
    C_i     |  100   |  200   |  200   | 
    d_i     |  200   |  500   |  400   | 

    Task1 < Task2 < Task3

*/

// variaveis usadas para a criar as tasks  

#define HIPERPERIODO 500
#define chegada1 0 
#define chegada2 0 
#define chegada3 200
#define computacao1 100
#define computacao2 200
#define computacao3 200
#define fim1 200
#define fim2 500
#define fim3 400

// bibliotecas incluidas

#include <kernel.hpp>
#include <edfsched.hpp>
#include <jtrace.hpp>
#include <texttrace.hpp>
#include <json_trace.hpp>
#include <rttask.hpp>
#include <instr.hpp>

using namespace MetaSim;
using namespace RTSim;

int main()
{
    try {

        cout << "Bem-vindos a nova versao do ENMA CORE =)" << endl;
        
        // arquivos estao sendo gerados

        SIMUL.dbg.enable("All");
        SIMUL.dbg.setStream("debug.txt");
        
        // a linha comentada abaixo deveria gerar o plot no Rttracer

        // JavaTrace jtrace("trace.trc");

        TextTrace ttrace("trace.txt");
        JSONTrace jtrace("trace.json");

        // ativando o escalonador edf do kernel
  
        cout << "Inicializando escalonador e kernel... " << endl;
        
        EDFScheduler edfsched; // cria o escalonador EDF
        RTKernel kern(&edfsched); // cria o kernl do sistema

        // cria a Task 1 com as especificacoes da tabela 

        cout << "Criando Task 1" << endl;
        PeriodicTask t1(computacao1, fim1, chegada1, "Task 1");

        // ajusta o WCET da Task 1

        cout << "Ajustando WCET da Task 1" << endl;
        t1.insertCode("fixed(200);");
        // t1.setAbort(false);
        
        cout << "Criando Task 2" << endl;
        PeriodicTask t2(computacao2, fim2, chegada2, "Task 2");;

        cout << "Ajustando WCET da Task 2" << endl;
        t2.insertCode("fixed(500);");
        // t2.setAbort(false);

        cout << "Criando Task 3" << endl;
        PeriodicTask t3(computacao3, fim3, chegada3, "Task 3");
        
        cout << "Ajustando WCET da Task 3" << endl;
        t3.insertCode("fixed(400);");
        // t3.setAbort(false);

        cout << "Adicionando as configuracoes necessarias..." << endl;
	
        // habilita as Tasks na escala em formato de texto 

        ttrace.attachToTask(t1);
        ttrace.attachToTask(t2);
        ttrace.attachToTask(t3);
        
        jtrace.attachToTask(t1);
        jtrace.attachToTask(t2);
        jtrace.attachToTask(t3);
        

        cout << "Adicionando tarefas ao kernel..." << endl;

        // adciona as Tasks ao kernel

        kern.addTask(t1, "");
        kern.addTask(t2, "");
        kern.addTask(t3, "");

        //  a linha a seguir serve caso seja adicionada uma nova Task

        // kern.addTask(t4, "");
        
  
        cout << "Simulando..." << endl;
        
        // simulacao das Tasks

        SIMUL.run(HIPERPERIODO);
        cout << "Hardware configurado com sucesso!" << endl;

        // caso ocorra alguma falha ele executa o catch
   
    } catch (BaseExc &e) {
        cout << "Hardware desconhecido!" << endl;
        cout << e.what() << endl;
    }
}
