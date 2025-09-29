
//Compra de ingressos em eventos

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <stdlib.h>

using namespace std;

struct eventos {
    int id_usuario;
    char nome[162];
    char cpf[20];
    short nascimento;
    char tipo_evento[100];

    void imprime() {
        cout << id_usuario << endl
             << nome << endl
             << cpf << endl
             << nascimento << endl
             << tipo_evento << endl;
    }
};

void salvar_no_arquivo(eventos dados[], int total) {
    ofstream arquivo("arquivo_csv_projeto.csv");
    if (!arquivo) {
        cerr << "\033[1;31mErro ao abrir arquivo para escrita!\033[0m" << endl;
        return;
    }
    
    arquivo << "#ID,Nome,CPF,Nascimento,Evento" << endl;
    
    for (int i = 0; i < total; i++) {
        arquivo << dados[i].id_usuario << ","
                << dados[i].nome << ","
                << dados[i].cpf << ","
                << dados[i].nascimento << ","
                << dados[i].tipo_evento << endl;
    }
}

void insertion(eventos vetor[], int tamanho) {
    for (int i = 1; i < tamanho; i++) {
        eventos chave = vetor[i];
        int j = i - 1;

        while (j >= 0 and vetor[j].id_usuario > chave.id_usuario) {
            vetor[j + 1] = vetor[j];
            j--;
        }
        vetor[j + 1] = chave;
    }
    salvar_no_arquivo(vetor, tamanho);
}

void insertion_cpf(eventos vetor[], int tamanho) {
    for (int i = 1; i < tamanho; i++) {
        eventos chave = vetor[i];
        int j = i - 1;

        while (j >= 0 and strcmp(vetor[j].cpf, chave.cpf) > 0) {
            vetor[j + 1] = vetor[j];
            j--;
        }
        vetor[j + 1] = chave;
    }
    salvar_no_arquivo(vetor, tamanho);
}

void imprimeDados(eventos dados[], int tam) {
    cout << "\033[1;36m____________________________________________________________________________\033[0m" << endl;
    for (int i = 0; i < tam; i++) {
        cout << dados[i].id_usuario << ", "
             << dados[i].nome << ", "
             << dados[i].cpf << ", "
             << dados[i].nascimento << ", "
             << dados[i].tipo_evento
             << endl;
        cout << "\033[1;36m____________________________________________________________________________\033[0m" << endl;
    }
}

void qtd_imprimir(eventos dados[], int numRegistros) {
    char min_char[20];
    char max_char[20];
    int min = 0;
    int max = 0;
    
    cout << "\033[38;5;208mNumero minimo de posicoes: \033[0m" << "1" << endl;
    cout << "\033[38;5;208mNumero maximo de posicoes: \033[0m" << numRegistros << endl;
    
    cin.ignore();
    
    // verifica se min é um número
    bool min_valido = false;
    while (!min_valido) {
        cout << "\033[38;5;208mDeseja que a impressao comece da posicao: \033[0m";
        cin.getline(min_char, 20);
        
        bool apenas_numeros = true;
        int tamanho = strlen(min_char);
        for (int i = 0; i < tamanho && apenas_numeros; i++) {
            if (min_char[i] < '0' || min_char[i] > '9') {
                apenas_numeros = false;
            }
        }
        
        if (!apenas_numeros || tamanho == 0) {
            cout << "\033[1;31mEntrada inválida. Digite apenas numeros.\033[0m" << endl;
        } else {
            min = 0;
            for (int i = 0; i < tamanho; i++) {
                min = min * 10 + (min_char[i] - '0');
            }
            
            if (min < 1 || min > numRegistros) {
                cout << "\033[1;31mPosicao deve estar entre 1 e " << numRegistros << ". Tente novamente.\033[0m" << endl;
            } else {
                min_valido = true;
            }
        }
    }
    //verifica se max é um número
    bool max_valido = false;
    while (!max_valido) {
        cout << "\033[38;5;208mE termine na posicao: \033[0m";
        cin.getline(max_char, 20);
        
        bool apenas_numeros = true;
        int tamanho = strlen(max_char);
        for (int i = 0; i < tamanho && apenas_numeros; i++) {
            if (max_char[i] < '0' || max_char[i] > '9') {
                apenas_numeros = false;
            }
        }
        
        if (!apenas_numeros || tamanho == 0) {
            cout << "\033[1;31mEntrada inválida. Digite apenas numeros.\033[0m" << endl;
        } else {
            max = 0;
            for (int i = 0; i < tamanho; i++) {
                max = max * 10 + (max_char[i] - '0');
            }
            
            if (max < 1 || max > numRegistros) {
                cout << "\033[1;31mPosicao deve estar entre 1 e " << numRegistros << ". Tente novamente.\033[0m" << endl;
            } else if (max < min) {
                cout << "\033[1;31mPosicao final deve ser maior ou igual a posicao inicial " << min << ". Tente novamente.\033[0m" << endl;
            } else {
                max_valido = true;
            }
        }
    }
     
    cout << endl << "\033[1;36m____________________________________________________________________________\033[0m" << endl;
    for (int i = min - 1; i < max; i++) {
        cout << dados[i].id_usuario << ", "
             << dados[i].nome << ", "
             << dados[i].cpf << ", "
             << dados[i].nascimento << ", "
             << dados[i].tipo_evento
             << endl;
        cout << "\033[1;36m____________________________________________________________________________\033[0m" << endl;
    }
}

void cadastro_novo_usuario(eventos novo, eventos vetor[], int numRegistro) {
    bool id_valido = false;
    char entrada[20];
    
    cin.ignore();
    
    while (!id_valido) {
        cout << "\033[38;5;208mCrie seu id pessoal (4 digitos no maximo): \033[0m" << endl;
        cin.getline(entrada, 20);
        
        bool apenas_numeros = true;
        int tamanho = strlen(entrada);
        for (int i = 0; i < tamanho and apenas_numeros; i++) {
            if (entrada[i] < '0' or entrada[i] > '9') {
                apenas_numeros = false;
            }
        }
        
        if (!apenas_numeros or tamanho == 0) {
            cout << "\033[1;31mEntrada inválida. Digite apenas numeros.\033[0m" << endl;
        } else {
            int id = 0;
            for (int i = 0; i < tamanho; i++) {
                id = id * 10 + (entrada[i] - '0');
            }
            
            if (id <= 0 or id > 9999) {
                cout << "\033[1;31mId deve ter entre 1 e 9999. Tente novamente.\033[0m" << endl;
            } else {
                bool id_existente = false;
                int i = 0;
                while (i < numRegistro and !id_existente) {
                    if (id == vetor[i].id_usuario) {
                        id_existente = true;
                    }
                    i++;
                }
                
                if (id_existente) {
                    cout << "\033[1;31mId já existente. Por favor, tente outro.\033[0m" << endl;
                } else {
                    novo.id_usuario = id;
                    id_valido = true;
                }
            }
        }
    }
    
    bool nome_valido;
    do {
        cout << "\033[38;5;208mNome do usuario (apenas letras e espacos): \033[0m" << endl;
        cin.getline(novo.nome, 162);
        
        nome_valido = true;
        int tamanho = strlen(novo.nome);
        
        // Verifica se está vazio
        if(tamanho == 0) {
            cout << "\033[1;31mO nome precisa ser informado!\033[0m" << endl;
            nome_valido = false;
        } else {
            // Verifica cada caractere
            int i = 0;
            while(i < tamanho && nome_valido) {
                char c = novo.nome[i];
                if(!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == ' ')) {
                    nome_valido = false;
                }
                i++;
            }
            
            if(!nome_valido) {
                cout << "\033[1;31mNome invalido! Use apenas letras e espacos.\033[0m" << endl;
            }
        }
    } while(strlen(novo.nome) == 0 || !nome_valido);
    
    cout << "\033[38;5;208mSeu CPF, sem .(ponto) e -(traco): \033[0m" << endl;
    bool cpf_valido = false;
    while (!cpf_valido) {
        cin.getline(novo.cpf, 20);

        int tamanho = strlen(novo.cpf);
        int qtd_digitos = 0;
        bool apenas_numeros = true;

        for (int i = 0; i < tamanho; i++) {
            if (novo.cpf[i] >= '0' and novo.cpf[i] <= '9') {
                qtd_digitos++;
            } else {
                apenas_numeros = false;
            }
        }
        if (qtd_digitos == 11 and apenas_numeros) {
            bool cpf_existente = false;
            int i = 0;
            while (i < numRegistro and !cpf_existente) {
                if (strcmp(novo.cpf, vetor[i].cpf) == 0) {
                    cpf_existente = true;
                }
                i++;
            }
            if (cpf_existente) {
                cout << "\033[1;31mCPF ja cadastrado, por favor tente outro!\033[0m" << endl;
                cpf_valido = false;
            } else {
                cpf_valido = true;
            }
        } else {
            cout << "\033[1;31mCPF invalido. Digite novamente (somente numeros, 11 digitos): \033[0m" << endl;
        }
    }

    char escrito[20];
    bool ano_valido = false;
    
    while (!ano_valido) {
        cout << "\033[38;5;208mDigite o ano de nascimento: \033[0m" << endl;
        cin.getline(escrito, 20);

        bool apenas_numeros = true;
        int tamanho = strlen(escrito);
        for (int i = 0; i < tamanho && apenas_numeros; i++) {
            if (escrito[i] < '0' || escrito[i] > '9') {
                apenas_numeros = false;
            }
        }

        if (!apenas_numeros || tamanho == 0) {
            cout << "\033[1;31mEntrada inválida. Digite apenas numeros.\033[0m" << endl;
        } else {
            int ano = 0;
            for (int i = 0; i < tamanho; i++) {
                ano = ano * 10 + (escrito[i] - '0');
            }

            if (ano < 1900 || ano > 2025) {
                cout << "\033[1;31mAno invalido! Digite um ano entre 1900 e 2025.\033[0m" << endl;
            } else if (2025 - ano < 18) {
                cout << "\033[1;31mProibido menores de 18 anos!\033[0m" << endl;
            } else {
                novo.nascimento = ano;
                ano_valido = true;
            }
        }
    }

    char escolha_evento[2];
    bool evento_valido = false;

    cout << "\033[38;5;208mEventos disponiveis:\033[0m" << endl
         << "\033[1;33m|1 - Anos 80 - Flashback Neon\033[0m" << endl
         << "\033[1;33m|2 - Festa Tropical / Luau - Noite Havaiana\033[0m" << endl
         << "\033[1;33m|3 - Fantasia - Mundo Encantado\033[0m" << endl
         << "\033[1;33m|4 - Festa Junina - Arraia do Povo\033[0m" << endl
         << "\033[1;33m|5 - Halloween - Noite do Terror\033[0m" << endl;

    while (!evento_valido) {
        cout << "\033[38;5;208mDigite o numero do evento escolhido: \033[0m";
        cin >> escolha_evento;
        cout << endl;
        cin.ignore();

        if (strcmp(escolha_evento, "1") == 0) {
            strcpy(novo.tipo_evento, "Anos 80 - Flashback Neon");
            evento_valido = true;
        } else if (strcmp(escolha_evento, "2") == 0) {
            strcpy(novo.tipo_evento, "Festa Tropical / Luau - Noite Havaiana");
            evento_valido = true;
        } else if (strcmp(escolha_evento, "3") == 0) {
            strcpy(novo.tipo_evento, "Fantasia - Mundo Encantado");
            evento_valido = true;
        } else if (strcmp(escolha_evento, "4") == 0) {
            strcpy(novo.tipo_evento, "Festa Junina - Arraia do Povo");
            evento_valido = true;
        } else if (strcmp(escolha_evento, "5") == 0) {
            strcpy(novo.tipo_evento, "Halloween - Noite do Terror");
            evento_valido = true;
        } else {
            cout << "\033[1;31mEvento inexistente! Por favor, escolha um dos eventos listados acima.\033[0m" << endl;
        }
    }

    cout << "\033[92mSEU LOGIN:\033[0m" << endl
         << "\033[92mID:\033[0m " << novo.id_usuario << endl
         << "\033[92mNOME:\033[0m " << novo.nome << endl
         << "\033[92mCPF:\033[0m " << novo.cpf << endl
         << "\033[92mANO DE NASCIMENTO: \033[0m" << novo.nascimento << endl
         << "\033[92mEVENTO ESCOLHIDO:\033[0m " << novo.tipo_evento << endl;
    cout << endl;
    
    vetor[numRegistro] = novo;
    salvar_no_arquivo(vetor, numRegistro + 1);
    cout << "\033[1;32mCadastrado com Sucesso!\033[0m" << endl;
}

void excluir_usuario(eventos dados[], int& total) {
    char cpf_buscado[20];
    
    cout << "\033[38;5;208mDigite o CPF do usuario a ser excluido: \033[0m";
    cin.ignore();
    cin.getline(cpf_buscado, 20);
    
    bool encontrado = false;
    int indice = -1;
    bool confirmado = false;
    
    for (int i = 0; i < total && !encontrado; i++) {
        if (strcmp(dados[i].cpf, cpf_buscado) == 0) {
            encontrado = true;
            indice = i;
        }
    }
    
    if (encontrado) {
        cout << "\033[1;32mUSUARIO ENCONTRADO.\033[0m" << endl;
        dados[indice].imprime();
        
        cout << endl;
        
        char resposta;
        cout << "\033[1;31mDeseja realmente excluir esta conta?\033[0m" << endl
             << "\033[1;31mDigite 's' para prosseguir ou qualquer outra letra ou numero para cancelar a operacao \033[0m";
        cin >> resposta;
        cin.ignore();
        
        if (resposta == 's' || resposta == 'S') {
            confirmado = true;
        }
        
        if (confirmado) {
            for (int j = indice; j < total - 1; j++) {
                dados[j] = dados[j + 1];
            }
            total--;
            salvar_no_arquivo(dados, total);
            cout << "\033[1;32mConta excluida com sucesso.\033[0m" << endl;
        } else {
            cout << "\033[1;32mOperacao cancelada! Agradecemos por continuar conosco.:)\033[0m" << endl;
        }
    } else {
        cout << "\033[1;31mCPF nao encontrado.\033[0m" << endl;
    }
}

void editar_dados_Id(eventos dados[], int numRegistro) {
    int id_procurado;
    int indice_encontrado = -1;
    int pos_inicial = 0;
    int pos_final = numRegistro - 1;
    int meio;
    bool encontrado = false;
    char escolha_evento[2];
    bool evento_valido = false;
   
    cout << "\033[38;5;208mInsira o Id procurado: \033[0m";
    cin >> id_procurado;
  
    while (pos_inicial <= pos_final) {
        meio = (pos_inicial + pos_final) / 2;
        if (id_procurado == dados[meio].id_usuario) {
            indice_encontrado = meio;
            pos_inicial = pos_final + 1;
            encontrado = true;
        } else {
            if (id_procurado > dados[meio].id_usuario) pos_inicial = meio + 1;
            else pos_final = meio - 1;
        }
    }
    
    if (encontrado == false) {
        cout << "\033[1;31mId nao encontrado, insira um Id existente: \033[0m";
        cin >> id_procurado;
    } else { 
        bool confirma = false;
        while(!confirma) {
            char escolha[2];

            cout << "\033[1;31mAo editar os dados, os mesmos ficarao salvos ao termino dessa aplicacao\033[0m" << endl
                 << "\033[1;31mDigite 's' para prosseguir ou qualquer outra letra ou numero para cancelar a operacao \033[0m";
             
            cin.ignore();
            cin >> escolha;
            cin.ignore();
            
            if(strcmp(escolha, "s")==0 || strcmp(escolha, "S")==0) {
                bool nome_valido;
                do {
                    cout << "\033[38;5;208mNome do usuario (apenas letras e espacos): \033[0m" << endl;
                    cin.getline(dados[indice_encontrado].nome, 162);
                    
                    nome_valido = true;
                    int tamanho = strlen(dados[indice_encontrado].nome);
                    
                    // Verifica se está vazio
                    if(tamanho == 0) {
                        cout << "\033[1;31mO nome precisa ser informado!\033[0m" << endl;
                        nome_valido = false;
                    } else {
                    // Verifica cada caractere
                        int i = 0;
                        while(i < tamanho && nome_valido) {
                            char c = dados[indice_encontrado].nome[i];
                            if(!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == ' ')) {
                                nome_valido = false;
                            }
                            i++;
                        }
                    
                        if(!nome_valido) {
                        cout << "\033[1;31mNome invalido! Use apenas letras e espacos.\033[0m" << endl;
                        }
                    }
                } while(strlen(dados[indice_encontrado].nome) == 0 || !nome_valido);
                
                cout << "\033[38;5;208mCPF: \033[0m" << endl;
                bool cpf_valido = false;
                while (!cpf_valido) {
                    cin.getline(dados[indice_encontrado].cpf, 20);

                    int tamanho = strlen(dados[indice_encontrado].cpf);
                    int qtd_digitos = 0;
                    bool apenas_numeros = true;

                    for (int i = 0; i < tamanho; i++) {
                        if (dados[indice_encontrado].cpf[i] >= '0' and dados[indice_encontrado].cpf[i] <= '9') {
                            qtd_digitos++;
                        } else {
                            apenas_numeros = false;
                        }
                    }

                    if (qtd_digitos == 11 and apenas_numeros) {
                        cpf_valido = true;
                    } else {
                        cout << "\033[1;31mCPF invalido. Digite novamente (somente numeros, 11 digitos): \033[0m" << endl;
                    }
                }
                    
                char escrito[20];
                bool ano_valido = false;
                
                while (!ano_valido) {
                    cout << "\033[38;5;208mDigite o ano de nascimento: \033[0m" << endl;
                    cin.getline(escrito, 20);

                    bool apenas_numeros = true;
                    int tamanho = strlen(escrito);
                    for (int i = 0; i < tamanho && apenas_numeros; i++) {
                        if (escrito[i] < '0' || escrito[i] > '9') {
                            apenas_numeros = false;
                        }
                    }

                    if (!apenas_numeros || tamanho == 0) {
                        cout << "\033[1;31mEntrada inválida. Digite apenas numeros.\033[0m" << endl;
                    } else {
                        int ano = 0;
                        for (int i = 0; i < tamanho; i++) {
                            ano = ano * 10 + (escrito[i] - '0');
                        }

                        if (ano < 1900 || ano > 2025) {
                            cout << "\033[1;31mAno invalido! Digite um ano entre 1900 e 2025.\033[0m" << endl;
                        } else if (2025 - ano < 18) {
                            cout << "\033[1;31mProibido menores de 18 anos!\033[0m" << endl;
                        } else {
                            dados[indice_encontrado].nascimento = ano;
                            ano_valido = true;
                        }
                    }
                }
                cin.ignore();
                   
                cout << endl << "\033[38;5;208mEscolha o tipo de evento!\033[0m" << endl << endl;
                cout << "\033[1;36mEventos disponiveis:\033[0m" << endl << endl
                << "\033[1;38;5;205m1 - Anos 80 - Flashback Neon\033[0m" << endl
                << "\033[1;38;5;205m2 - Festa Tropical / Luau - Noite Havaiana\033[0m" << endl
                << "\033[1;38;5;205m3 - Fantasia - Mundo Encantado\033[0m" << endl
                << "\033[1;38;5;205m4 - Festa Junina - Arraia do Povo\033[0m" << endl
                << "\033[1;38;5;205m5 - Halloween - Noite do Terror\033[0m" << endl;
                
                while (!evento_valido) {
                    cout << endl << " \033[38;5;208mDigite o numero do evento escolhido: \033[0m";
                    cin >> escolha_evento;
                    cout << endl;
                    cin.ignore();

                    if (strcmp(escolha_evento, "1") == 0) {
                        strcpy(dados[indice_encontrado].tipo_evento, "Anos 80 - Flashback Neon");
                        evento_valido = true;
                    } else if (strcmp(escolha_evento, "2") == 0) {
                        strcpy(dados[indice_encontrado].tipo_evento, "Festa Tropical / Luau - Noite Havaiana");
                        evento_valido = true;
                    } else if (strcmp(escolha_evento, "3") == 0) {
                        strcpy(dados[indice_encontrado].tipo_evento, "Fantasia - Mundo Encantado");
                        evento_valido = true;
                    } else if (strcmp(escolha_evento, "4") == 0) {
                        strcpy(dados[indice_encontrado].tipo_evento, "Festa Junina - Arraia do Povo");
                        evento_valido = true;
                    } else if (strcmp(escolha_evento, "5") == 0) {
                        strcpy(dados[indice_encontrado].tipo_evento, "Halloween - Noite do Terror");
                        evento_valido = true;
                    } else {
                        cout << "\033[1;31mEvento inexistente! Por favor, escolha um dos eventos listados acima.\033[0m" << endl;
                    }
                }
                
                cout << "\033[92mLOGIN:\033[0m" << endl
                     << "\033[92mID:\033[0m " << dados[indice_encontrado].id_usuario << endl
                     << "\033[92mNOME:\033[0m " << dados[indice_encontrado].nome << endl
                     << "\033[92mCPF:\033[0m " << dados[indice_encontrado].cpf << endl
                     << "\033[92mANO DE NASCIMENTO: \033[0m" << dados[indice_encontrado].nascimento << endl
                     << "\033[92mEVENTO ESCOLHIDO:\033[0m " << dados[indice_encontrado].tipo_evento << endl;
                cout << endl;

                salvar_no_arquivo(dados, numRegistro);
                cout << "\033[1;32mDados atualizados com sucesso!\033[0m" << endl;
                confirma = true;
            } else {
                confirma = true;
                cout << "\033[1;32mOperacao cancelada com sucesso!.\033[0m" << endl;
            }
        }
    }
}

void editar_usuario_CPF(eventos dados[], int total) {
    int escolha_evento;
    bool evento_valido = false;
    char cpf_buscado[20];
    int indice_encontrado = -1;
    int pos_inicial = 0;
    int pos_final = total - 1;
    bool continuar_busca = true;

    cout << "\033[38;5;208mDigite o CPF do usuario que deseja editar: \033[0m";
    cin.ignore();
    cin.getline(cpf_buscado, 20);

    bool encontrado = false;
    while (pos_inicial <= pos_final && continuar_busca) {
        int meio = (pos_inicial + pos_final) / 2;
        int comparacao = strcmp(cpf_buscado, dados[meio].cpf);

        if (comparacao == 0) {
            indice_encontrado = meio;
            encontrado = true;
            continuar_busca = false;
        } else if (comparacao > 0) {
            pos_inicial = meio + 1;
        } else {
            pos_final = meio - 1;
        }
    }

    if (!encontrado) {
        cout << "\033[1;31mCPF não encontrado.\033[0m" << endl;
        return;
    } else {
        bool nome_valido;

        char resposta;
        cout << "\033[1;31mAo editar os dados, os mesmos ficarao salvos ao termino dessa aplicacao\033[0m" << endl
             << "\033[1;31mDigite 's' para prosseguir ou qualquer outra letra ou numero para cancelar a operacao \033[0m";        
        cin >> resposta;
        cin.ignore();

        if (resposta == 's' || resposta == 'S') {
            do {
                cout << "\033[38;5;208mNome do usuario (apenas letras e espacos): \033[0m" << endl;
                cin.getline(dados[indice_encontrado].nome, 162);
                
                nome_valido = true;
                int tamanho = strlen(dados[indice_encontrado].nome);
                
                // Verifica se está vazio
                if(tamanho == 0) {
                    cout << "\033[1;31mO nome precisa ser informado!\033[0m" << endl;
                    nome_valido = false;
                } else {
                    // Verifica cada caractere
                    int i = 0;
                    while(i < tamanho && nome_valido) {
                        char c = dados[indice_encontrado].nome[i];
                        if(!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == ' ')) {
                            nome_valido = false;
                        }
                        i++;
                    }
                    
                    if(!nome_valido) {
                        cout << "\033[1;31mNome invalido! Use apenas letras e espacos.\033[0m" << endl;
                    }
                }
            } while(strlen(dados[indice_encontrado].nome) == 0 || !nome_valido);

            char escrito[20];
            bool ano_valido = false;
            
            while (!ano_valido) {
                cout << "\033[38;5;208mDigite o ano de nascimento: \033[0m" << endl;
                cin.getline(escrito, 20);

                bool apenas_numeros = true;
                int tamanho = strlen(escrito);
                for (int i = 0; i < tamanho && apenas_numeros; i++) {
                    if (escrito[i] < '0' || escrito[i] > '9') {
                        apenas_numeros = false;
                    }
                }

                if (!apenas_numeros || tamanho == 0) {
                    cout << "\033[1;31mEntrada inválida. Digite apenas numeros.\033[0m" << endl;
                } else {
                    int ano = 0;
                    for (int i = 0; i < tamanho; i++) {
                        ano = ano * 10 + (escrito[i] - '0');
                    }

                    if (ano < 1900 || ano > 2025) {
                        cout << "\033[1;31mAno invalido! Digite um ano entre 1900 e 2025.\033[0m" << endl;
                    } else if (2025 - ano < 18) {
                        cout << "\033[1;31mProibido menores de 18 anos!\033[0m" << endl;
                    } else {
                        dados[indice_encontrado].nascimento = ano;
                        ano_valido = true;
                    }
                }
            }

            cout << endl << "\033[38;5;208mEscolha o tipo de evento!\033[0m" << endl << endl;
            cout << "\033[1;36mEventos disponiveis:\033[0m" << endl << endl
                 << "\033[1;38;5;205m1 - Anos 80 - Flashback Neon\033[0m" << endl
                 << "\033[1;38;5;205m2 - Festa Tropical / Luau - Noite Havaiana\033[0m" << endl
                 << "\033[1;38;5;205m3 - Fantasia - Mundo Encantado\033[0m" << endl
                 << "\033[1;38;5;205m4 - Festa Junina - Arraiá do Povo\033[0m" << endl
                 << "\033[1;38;5;205m5 - Halloween - Noite do Terror\033[0m" << endl;

            while (!evento_valido) {
                cout << endl << "\033[38;5;208mDigite o numero do evento escolhido: \033[0m";
                cin >> escolha_evento;
                cout << endl;
                cin.ignore();

                if (escolha_evento == 1) {
                    strcpy(dados[indice_encontrado].tipo_evento, "Anos 80 - Flashback Neon");
                    evento_valido = true;
                } else if (escolha_evento == 2) {
                    strcpy(dados[indice_encontrado].tipo_evento, "Festa Tropical / Luau - Noite Havaiana");
                    evento_valido = true;
                } else if (escolha_evento == 3) {
                    strcpy(dados[indice_encontrado].tipo_evento, "Fantasia - Mundo Encantado");
                    evento_valido = true;
                } else if (escolha_evento == 4) {
                    strcpy(dados[indice_encontrado].tipo_evento, "Festa Junina - Arraiá do Povo");
                    evento_valido = true;
                } else if (escolha_evento == 5) {
                    strcpy(dados[indice_encontrado].tipo_evento, "Halloween - Noite do Terror");
                    evento_valido = true;
                } else {
                    cout << "\033[1;31mEvento inexistente! Por favor, escolha um dos eventos listados acima.\033[0m" << endl;
                }
            }

            cout << "\033[92mSEU LOGIN:\033[0m" << endl
                 << "\033[92mID:\033[0m " << dados[indice_encontrado].id_usuario << endl
                 << "\033[92mNOME:\033[0m " << dados[indice_encontrado].nome << endl
                 << "\033[92mCPF:\033[0m " << dados[indice_encontrado].cpf << endl
                 << "\033[92mANO DE NASCIMENTO: \033[0m" << dados[indice_encontrado].nascimento << endl
                 << "\033[92mEVENTO ESCOLHIDO:\033[0m " << dados[indice_encontrado].tipo_evento << endl;
            cout << endl;

            // Confirmação antes de salvar
            salvar_no_arquivo(dados, total);
            cout << "\033[1;32mDados atualizados com sucesso!\033[0m" << endl;
        } else {
            cout << "\033[1;32mOperacao cancelada com sucesso!.\033[0m" << endl;
        }
    }
}

void binario(eventos dadosPessoas[], int numRegistro) {
    ofstream arquivo("projeto_binario.bin", ios::binary);
    ifstream arquivoLido("projeto_binario.bin", ios::binary);
    
    arquivo.write((const char*)(dadosPessoas), numRegistro * sizeof(eventos));
    arquivoLido.read((char*)(dadosPessoas), sizeof(eventos) * numRegistro);
    
    for (int i = 0; i < numRegistro; i++) {
        cout << dadosPessoas[i].id_usuario << ", "
             << dadosPessoas[i].nome << ", "    
             << dadosPessoas[i].cpf << ", "
             << dadosPessoas[i].nascimento << ", "
             << dadosPessoas[i].tipo_evento << "." << endl;        
    }
    arquivo.close();
    arquivoLido.close();
}

void limparTela() {
    system("cls || clear"); // Funciona no Windows (cls) e Linux/macOS (clear)
}

int main() {
    eventos pessoa;
    eventos* dadosPessoas;
    string linha;
    char lixo;
    int numRegistros = 0;

    ifstream arquivo_csv("arquivo_csv_projeto.csv");
    if (!arquivo_csv) {
        cout << "\033[1;31mArquivo CSV nao esta aberto!\033[0m" << endl;
    } else {
        getline(arquivo_csv, linha);
        int totalLidos = 0;
        int tamanhoIndiceAtual = 10;
        dadosPessoas = new eventos[tamanhoIndiceAtual];

        while (arquivo_csv >> pessoa.id_usuario) {
            arquivo_csv >> lixo;
            arquivo_csv.getline(pessoa.nome, 162, ',');
            arquivo_csv.getline(pessoa.cpf, 20, ',');
            arquivo_csv >> pessoa.nascimento;
            arquivo_csv >> lixo;
            arquivo_csv.getline(pessoa.tipo_evento, 100);

            dadosPessoas[totalLidos] = pessoa;
            totalLidos++;

            if (totalLidos >= tamanhoIndiceAtual) {
                tamanhoIndiceAtual += 10;
                eventos* novo_vetor = new eventos[tamanhoIndiceAtual];
                for (int i = 0; i < totalLidos; i++) {
                    novo_vetor[i] = dadosPessoas[i];
                }
                delete[] dadosPessoas;
                dadosPessoas = novo_vetor;
            }
        }
        numRegistros = totalLidos;
    }

    char opcao[2];
    char opcao_busca[2];
    bool opcao_valida = true;
    char resposta = 's';
    
    do {
        limparTela();

        cerr << "\033[1;35m--------------------------------------------------------\033[0m" << endl;
        cerr << "\033[1;35m                     MENU PRINCIPAL           \033[0m" << endl
             << "\033[1;35m                       Bem-vindo!            \033[0m" << endl
             << "\033[1;35m--------------------------------------------------------\033[0m" << endl
             << "\033[38;5;208mEscolha uma das opcoes abaixo para continuar:\033[0m" << endl
             << endl << endl
             << "\033[1;33m|1 - Para imprimir todos os dados do arquivo.\033[0m" << endl
             << "\033[1;33m|2 - Para se cadastrar.\033[0m" << endl
             << "\033[1;33m|3 - Para excluir a conta.\033[0m" << endl 
             << "\033[1;33m|4 - Para buscar e editar os dados de usuario.\033[0m" << endl
             << "\033[1;33m|5 - Para imprimir a quantidade desejada de dados.\033[0m" << endl
             << "\033[1;33m|6 - Para sair.\033[0m" << endl
             << endl
             << "\033[38;5;208mDigite sua opcao: \033[0m";
        
        cin >> opcao;
        
        if (strlen(opcao) == 1 && opcao[0] >= '1' && opcao[0] <= '6') {
            if (strcmp(opcao, "1") == 0) {
                limparTela();
                insertion(dadosPessoas, numRegistros);
                imprimeDados(dadosPessoas, numRegistros);

                cout << "\n\033[38;5;208mDeseja realizar outra operacao?\033[0m" << endl
                     << "\n\033[38;5;208mDigite 's' para realizar outra operacao ou qualquer outra letra ou numero caso queira encerrar o sistema! \033[0m" << endl;				
               
                cin >> resposta;    
            } 
            else if (strcmp(opcao, "2") == 0) {
                limparTela();
                cadastro_novo_usuario(pessoa, dadosPessoas, numRegistros);
                numRegistros++;

                cout << "\n\033[38;5;208mDeseja realizar outra operacao?\033[0m" << endl
                     << "\n\033[38;5;208mDigite 's' para realizar outra operacao ou qualquer outra letra ou numero caso queira encerrar o sistema! \033[0m" << endl;
				
                cin >> resposta;    
            } 
            else if (strcmp(opcao, "3") == 0) {
                limparTela();
                excluir_usuario(dadosPessoas, numRegistros);

                cout << "\n\033[38;5;208mDeseja realizar outra operacao?\033[0m" << endl
                     << "\n\033[38;5;208mDigite 's' para realizar outra operacao ou qualquer outra letra ou numero caso queira encerrar o sistema! \033[0m" << endl;
				
                cin >> resposta;    
            } 
            else if (strcmp(opcao, "4") == 0) {
                limparTela();
                cout << "\033[38;5;208mDigite sua opcao de busca: \033[0m" << endl
                     << "\033[38;5;208m|1 - para fazer a buscar por ID \033[0m" << endl
                     << "\033[38;5;208m|2 - para fazer a buscar por CPF \033[0m" << endl;
                
                bool busca_valida = false;
                
                while(!busca_valida) {
                    cin >> opcao_busca;
                    
                    if (strlen(opcao_busca) == 1 && (opcao_busca[0] == '1' || opcao_busca[0] == '2')) {
                        if (strcmp(opcao_busca, "1") == 0) {
                            insertion(dadosPessoas, numRegistros);
                            editar_dados_Id(dadosPessoas, numRegistros);    

                            cout << "\n\033[38;5;208mDeseja realizar outra operacao?\033[0m" << endl
                                 << "\n\033[38;5;208mDigite 's' para realizar outra operacao ou qualquer outra letra ou numero caso queira encerrar o sistema! \033[0m" << endl;
                            
                            cin >> resposta;
                            cin.ignore();
                            busca_valida = true;
                        } 
                        else {
                            insertion_cpf(dadosPessoas, numRegistros);
                            editar_usuario_CPF(dadosPessoas, numRegistros);

                            cout << "\n\033[38;5;208mDeseja realizar outra operacao?\033[0m" << endl
                                 << "\n\033[38;5;208mDigite 's' para realizar outra operacao ou qualquer outra letra ou numero caso queira encerrar o sistema! \033[0m" << endl;
                            
                            cin >> resposta;
                            cin.ignore();
                            busca_valida = true;
                        }
                    } 
                    else {
                        cout << "\033[1;31mOpcao de busca invalida!\033[0m" << endl 
                             << "\033[1;31mSelecione uma opcao valida!\033[0m" << endl;
                    }
                } 
            }
            else if (strcmp(opcao, "5") == 0) {
                limparTela();
                qtd_imprimir(dadosPessoas, numRegistros);
                cout << "\n\033[38;5;208mDeseja realizar outra operacao?\033[0m" << endl
                     << "\n\033[38;5;208mDigite 's' para realizar outra operacao ou qualquer outra letra ou numero caso queira encerrar o sistema! \033[0m" << endl;

                cin >> resposta;
                cin.ignore();
            } 
            else if (strcmp(opcao, "6") == 0) {
                insertion(dadosPessoas, numRegistros);
                opcao_valida = false;
                resposta = 'n';
            }
        } 
    } while (opcao_valida && (resposta == 's' || resposta == 'S'));
    
    insertion(dadosPessoas, numRegistros);

    cout << "\033[1;32mObrigado por usar nosso sistema! Ate logo.\033[0m" << endl;

    delete[] dadosPessoas;
    return 0;
}
