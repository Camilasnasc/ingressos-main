
//Compra de ingressos em eventos

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <stdlib.h>

using namespace std;

struct eventos {
    int id_usuario;
    string nome;
    string cpf;
    short nascimento;
    string tipo_evento;

    void imprime() {
        cout << id_usuario << endl
             << nome << endl
             << cpf << endl
             << nascimento << endl
             << tipo_evento << endl;
    }
};

// Le uma linha via cin.getline, valida que contem apenas digitos e esta
// dentro de [minValor, maxValor], repetindo o prompt ate ser valido.
int lerInteiroValidado(const string& prompt, int minValor, int maxValor, const string& mensagemForaDaFaixa) {
    int valor = 0;
    bool valido = false;

    while (!valido) {
        cout << prompt;
        char entrada[20];
        cin.getline(entrada, 20);

        bool apenas_numeros = true;
        int tamanho = strlen(entrada);
        for (int i = 0; i < tamanho && apenas_numeros; i++) {
            if (entrada[i] < '0' || entrada[i] > '9') {
                apenas_numeros = false;
            }
        }

        if (!apenas_numeros || tamanho == 0) {
            cout << "\033[1;31mEntrada inválida. Digite apenas numeros.\033[0m" << endl;
        } else {
            valor = 0;
            for (int i = 0; i < tamanho; i++) {
                valor = valor * 10 + (entrada[i] - '0');
            }

            if (valor < minValor || valor > maxValor) {
                cout << mensagemForaDaFaixa;
            } else {
                valido = true;
            }
        }
    }

    return valor;
}

// Le uma linha via cin.getline e valida que contem apenas letras e
// espacos e nao esta vazia, repetindo o prompt ate ser valido.
string lerNomeValidado() {
    char buffer_nome[162];
    bool nome_valido;

    do {
        cout << "\033[38;5;208mNome do usuario (apenas letras e espacos): \033[0m" << endl;
        cin.getline(buffer_nome, 162);

        nome_valido = true;
        int tamanho = strlen(buffer_nome);

        // Verifica se está vazio
        if (tamanho == 0) {
            cout << "\033[1;31mO nome precisa ser informado!\033[0m" << endl;
            nome_valido = false;
        } else {
            // Verifica cada caractere
            int i = 0;
            while (i < tamanho && nome_valido) {
                char c = buffer_nome[i];
                if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == ' ')) {
                    nome_valido = false;
                }
                i++;
            }

            if (!nome_valido) {
                cout << "\033[1;31mNome invalido! Use apenas letras e espacos.\033[0m" << endl;
            }
        }
    } while (strlen(buffer_nome) == 0 || !nome_valido);

    return string(buffer_nome);
}

// Le uma linha via cin.getline e valida que contem exatamente 11
// digitos numericos. Quando checarDuplicidade e true, tambem rejeita
// um CPF ja presente em vetor[0..total). O prompt inicial e impresso
// pelo chamador; esta funcao so reimprime as mensagens de erro.
string lerCpfValidado(const eventos vetor[], int total, bool checarDuplicidade) {
    char buffer_cpf[20];
    bool cpf_valido = false;

    while (!cpf_valido) {
        cin.getline(buffer_cpf, 20);

        int tamanho = strlen(buffer_cpf);
        int qtd_digitos = 0;
        bool apenas_numeros = true;

        for (int i = 0; i < tamanho; i++) {
            if (buffer_cpf[i] >= '0' and buffer_cpf[i] <= '9') {
                qtd_digitos++;
            } else {
                apenas_numeros = false;
            }
        }

        if (qtd_digitos == 11 and apenas_numeros) {
            if (checarDuplicidade) {
                bool cpf_existente = false;
                int i = 0;
                while (i < total and !cpf_existente) {
                    if (vetor[i].cpf == buffer_cpf) {
                        cpf_existente = true;
                    }
                    i++;
                }
                if (cpf_existente) {
                    cout << "\033[1;31mCPF ja cadastrado, por favor tente outro!\033[0m" << endl;
                } else {
                    cpf_valido = true;
                }
            } else {
                cpf_valido = true;
            }
        } else {
            cout << "\033[1;31mCPF invalido. Digite novamente (somente numeros, 11 digitos): \033[0m" << endl;
        }
    }

    return string(buffer_cpf);
}

// Tabela unica dos eventos disponiveis (indice 0 = evento "1", etc).
// Nota: o texto do evento 4 tinha duas grafias no codigo original
// ("Arraia do Povo" em cadastro_novo_usuario/editar_dados_Id e
// "Arraiá do Povo" em editar_usuario_CPF). Adotamos "Arraia do Povo"
// (sem acento) como texto canonico por ser a grafia usada em 2 dos 3
// pontos originais.
const string NOMES_EVENTOS[5] = {
    "Anos 80 - Flashback Neon",
    "Festa Tropical / Luau - Noite Havaiana",
    "Fantasia - Mundo Encantado",
    "Festa Junina - Arraia do Povo",
    "Halloween - Noite do Terror"
};

// Estilo visual do menu de eventos: cada ponto de chamada original
// tinha cores/layout proprios (e, no prompt de escolha do estilo
// EDITAR_ID, um espaco extra antes do texto que ja existia no
// codigo original) - preservados aqui para nao mudar a saida.
enum class EstiloMenuEvento { CADASTRO, EDITAR_ID, EDITAR_CPF };

// Imprime o menu de eventos (no estilo do chamador) e le a escolha
// (1-5) ate ser valida, retornando o nome do evento escolhido.
string escolherEvento(EstiloMenuEvento estilo) {
    if (estilo == EstiloMenuEvento::CADASTRO) {
        cout << "\033[38;5;208mEventos disponiveis:\033[0m" << endl
             << "\033[1;33m|1 - " << NOMES_EVENTOS[0] << "\033[0m" << endl
             << "\033[1;33m|2 - " << NOMES_EVENTOS[1] << "\033[0m" << endl
             << "\033[1;33m|3 - " << NOMES_EVENTOS[2] << "\033[0m" << endl
             << "\033[1;33m|4 - " << NOMES_EVENTOS[3] << "\033[0m" << endl
             << "\033[1;33m|5 - " << NOMES_EVENTOS[4] << "\033[0m" << endl;
    } else {
        cout << endl << "\033[38;5;208mEscolha o tipo de evento!\033[0m" << endl << endl;
        cout << "\033[1;36mEventos disponiveis:\033[0m" << endl << endl
             << "\033[1;38;5;205m1 - " << NOMES_EVENTOS[0] << "\033[0m" << endl
             << "\033[1;38;5;205m2 - " << NOMES_EVENTOS[1] << "\033[0m" << endl
             << "\033[1;38;5;205m3 - " << NOMES_EVENTOS[2] << "\033[0m" << endl
             << "\033[1;38;5;205m4 - " << NOMES_EVENTOS[3] << "\033[0m" << endl
             << "\033[1;38;5;205m5 - " << NOMES_EVENTOS[4] << "\033[0m" << endl;
    }

    char escolha_evento[2];
    bool evento_valido = false;
    string nomeEscolhido;

    while (!evento_valido) {
        if (estilo == EstiloMenuEvento::CADASTRO) {
            cout << "\033[38;5;208mDigite o numero do evento escolhido: \033[0m";
        } else if (estilo == EstiloMenuEvento::EDITAR_ID) {
            cout << endl << " \033[38;5;208mDigite o numero do evento escolhido: \033[0m";
        } else {
            cout << endl << "\033[38;5;208mDigite o numero do evento escolhido: \033[0m";
        }

        cin >> escolha_evento;
        cout << endl;
        cin.ignore();

        int indice = -1;
        for (int i = 0; i < 5 && indice == -1; i++) {
            if (strcmp(escolha_evento, to_string(i + 1).c_str()) == 0) {
                indice = i;
            }
        }

        if (indice != -1) {
            nomeEscolhido = NOMES_EVENTOS[indice];
            evento_valido = true;
        } else {
            cout << "\033[1;31mEvento inexistente! Por favor, escolha um dos eventos listados acima.\033[0m" << endl;
        }
    }

    return nomeEscolhido;
}

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

// Ordena por id_usuario (porCpf = false) ou por cpf (porCpf = true) e
// reescreve o CSV com o resultado, como insertion/insertion_cpf faziam.
// id_usuario e cpf sao unicos entre os registros (regra de negocio),
// entao nunca ha empate no criterio de ordenacao.
void ordenarESalvar(eventos vetor[], int tamanho, bool porCpf) {
    if (porCpf) {
        sort(vetor, vetor + tamanho, [](const eventos& a, const eventos& b) {
            return a.cpf < b.cpf;
        });
    } else {
        sort(vetor, vetor + tamanho, [](const eventos& a, const eventos& b) {
            return a.id_usuario < b.id_usuario;
        });
    }
    salvar_no_arquivo(vetor, tamanho);
}

// Imprime um registro seguido da linha separadora, no formato usado
// por imprimeDados e qtd_imprimir.
void imprimeRegistro(const eventos& registro) {
    cout << registro.id_usuario << ", "
         << registro.nome << ", "
         << registro.cpf << ", "
         << registro.nascimento << ", "
         << registro.tipo_evento
         << endl;
    cout << "\033[1;36m____________________________________________________________________________\033[0m" << endl;
}

// Imprime o resumo "LOGIN" de um registro apos cadastro/edicao.
// cabecalho e recebido pronto (com cor) porque o texto varia entre
// chamadores: "SEU LOGIN:" em cadastro_novo_usuario/editar_usuario_CPF
// e apenas "LOGIN:" em editar_dados_Id - inconsistencia pre-existente
// preservada aqui.
void imprimeResumoLogin(const eventos& registro, const string& cabecalho) {
    cout << cabecalho << endl
         << "\033[92mID:\033[0m " << registro.id_usuario << endl
         << "\033[92mNOME:\033[0m " << registro.nome << endl
         << "\033[92mCPF:\033[0m " << registro.cpf << endl
         << "\033[92mANO DE NASCIMENTO: \033[0m" << registro.nascimento << endl
         << "\033[92mEVENTO ESCOLHIDO:\033[0m " << registro.tipo_evento << endl;
    cout << endl;
}

void imprimeDados(eventos dados[], int tam) {
    cout << "\033[1;36m____________________________________________________________________________\033[0m" << endl;
    for (int i = 0; i < tam; i++) {
        imprimeRegistro(dados[i]);
    }
}

void qtd_imprimir(eventos dados[], int numRegistros) {
    int min = 0;
    int max = 0;

    cout << "\033[38;5;208mNumero minimo de posicoes: \033[0m" << "1" << endl;
    cout << "\033[38;5;208mNumero maximo de posicoes: \033[0m" << numRegistros << endl;

    cin.ignore();

    string mensagemFaixaPosicao = "\033[1;31mPosicao deve estar entre 1 e " + to_string(numRegistros) + ". Tente novamente.\033[0m\n";

    // verifica se min é um número
    min = lerInteiroValidado("\033[38;5;208mDeseja que a impressao comece da posicao: \033[0m", 1, numRegistros, mensagemFaixaPosicao);

    //verifica se max é um número
    bool max_valido = false;
    while (!max_valido) {
        max = lerInteiroValidado("\033[38;5;208mE termine na posicao: \033[0m", 1, numRegistros, mensagemFaixaPosicao);

        if (max < min) {
            cout << "\033[1;31mPosicao final deve ser maior ou igual a posicao inicial " << min << ". Tente novamente.\033[0m" << endl;
        } else {
            max_valido = true;
        }
    }

    cout << endl << "\033[1;36m____________________________________________________________________________\033[0m" << endl;
    for (int i = min - 1; i < max; i++) {
        imprimeRegistro(dados[i]);
    }
}

void cadastro_novo_usuario(eventos novo, eventos vetor[], int numRegistro) {
    bool id_valido = false;

    cin.ignore();

    while (!id_valido) {
        int id = lerInteiroValidado(
            "\033[38;5;208mCrie seu id pessoal (4 digitos no maximo): \033[0m\n",
            1, 9999,
            "\033[1;31mId deve ter entre 1 e 9999. Tente novamente.\033[0m\n"
        );

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

    novo.nome = lerNomeValidado();

    cout << "\033[38;5;208mSeu CPF, sem .(ponto) e -(traco): \033[0m" << endl;
    novo.cpf = lerCpfValidado(vetor, numRegistro, true);

    bool ano_valido = false;

    while (!ano_valido) {
        int ano = lerInteiroValidado(
            "\033[38;5;208mDigite o ano de nascimento: \033[0m\n",
            1900, 2025,
            "\033[1;31mAno invalido! Digite um ano entre 1900 e 2025.\033[0m\n"
        );

        if (2025 - ano < 18) {
            cout << "\033[1;31mProibido menores de 18 anos!\033[0m" << endl;
        } else {
            novo.nascimento = ano;
            ano_valido = true;
        }
    }

    novo.tipo_evento = escolherEvento(EstiloMenuEvento::CADASTRO);

    imprimeResumoLogin(novo, "\033[92mSEU LOGIN:\033[0m");

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
        if (dados[i].cpf == cpf_buscado) {
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
                dados[indice_encontrado].nome = lerNomeValidado();

                cout << "\033[38;5;208mCPF: \033[0m" << endl;
                dados[indice_encontrado].cpf = lerCpfValidado(dados, numRegistro, false);
                    
                bool ano_valido = false;

                while (!ano_valido) {
                    int ano = lerInteiroValidado(
                        "\033[38;5;208mDigite o ano de nascimento: \033[0m\n",
                        1900, 2025,
                        "\033[1;31mAno invalido! Digite um ano entre 1900 e 2025.\033[0m\n"
                    );

                    if (2025 - ano < 18) {
                        cout << "\033[1;31mProibido menores de 18 anos!\033[0m" << endl;
                    } else {
                        dados[indice_encontrado].nascimento = ano;
                        ano_valido = true;
                    }
                }
                cin.ignore();
                   
                dados[indice_encontrado].tipo_evento = escolherEvento(EstiloMenuEvento::EDITAR_ID);

                imprimeResumoLogin(dados[indice_encontrado], "\033[92mLOGIN:\033[0m");

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
        int comparacao = strcmp(cpf_buscado, dados[meio].cpf.c_str());

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
        char resposta;
        cout << "\033[1;31mAo editar os dados, os mesmos ficarao salvos ao termino dessa aplicacao\033[0m" << endl
             << "\033[1;31mDigite 's' para prosseguir ou qualquer outra letra ou numero para cancelar a operacao \033[0m";
        cin >> resposta;
        cin.ignore();

        if (resposta == 's' || resposta == 'S') {
            dados[indice_encontrado].nome = lerNomeValidado();

            bool ano_valido = false;

            while (!ano_valido) {
                int ano = lerInteiroValidado(
                    "\033[38;5;208mDigite o ano de nascimento: \033[0m\n",
                    1900, 2025,
                    "\033[1;31mAno invalido! Digite um ano entre 1900 e 2025.\033[0m\n"
                );

                if (2025 - ano < 18) {
                    cout << "\033[1;31mProibido menores de 18 anos!\033[0m" << endl;
                } else {
                    dados[indice_encontrado].nascimento = ano;
                    ano_valido = true;
                }
            }

            dados[indice_encontrado].tipo_evento = escolherEvento(EstiloMenuEvento::EDITAR_CPF);

            imprimeResumoLogin(dados[indice_encontrado], "\033[92mSEU LOGIN:\033[0m");

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
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main() {
    eventos pessoa;
    vector<eventos> dadosPessoas;
    string linha;
    char lixo;
    int numRegistros = 0;

    ifstream arquivo_csv("arquivo_csv_projeto.csv");
    if (!arquivo_csv) {
        cout << "\033[1;31mArquivo CSV nao esta aberto!\033[0m" << endl;
    } else {
        getline(arquivo_csv, linha);

        while (arquivo_csv >> pessoa.id_usuario) {
            arquivo_csv >> lixo;
            getline(arquivo_csv, pessoa.nome, ',');
            getline(arquivo_csv, pessoa.cpf, ',');
            arquivo_csv >> pessoa.nascimento;
            arquivo_csv >> lixo;
            getline(arquivo_csv, pessoa.tipo_evento);

            dadosPessoas.push_back(pessoa);
        }
        numRegistros = dadosPessoas.size();
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
                ordenarESalvar(dadosPessoas.data(), numRegistros, false);
                imprimeDados(dadosPessoas.data(), numRegistros);

                cout << "\n\033[38;5;208mDeseja realizar outra operacao?\033[0m" << endl
                     << "\n\033[38;5;208mDigite 's' para realizar outra operacao ou qualquer outra letra ou numero caso queira encerrar o sistema! \033[0m" << endl;				
               
                cin >> resposta;    
            } 
            else if (strcmp(opcao, "2") == 0) {
                limparTela();
                if ((int)dadosPessoas.size() <= numRegistros) {
                    dadosPessoas.resize(numRegistros + 1);
                }
                cadastro_novo_usuario(pessoa, dadosPessoas.data(), numRegistros);
                numRegistros++;

                cout << "\n\033[38;5;208mDeseja realizar outra operacao?\033[0m" << endl
                     << "\n\033[38;5;208mDigite 's' para realizar outra operacao ou qualquer outra letra ou numero caso queira encerrar o sistema! \033[0m" << endl;
				
                cin >> resposta;    
            } 
            else if (strcmp(opcao, "3") == 0) {
                limparTela();
                excluir_usuario(dadosPessoas.data(), numRegistros);

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
                            ordenarESalvar(dadosPessoas.data(), numRegistros, false);
                            editar_dados_Id(dadosPessoas.data(), numRegistros);    

                            cout << "\n\033[38;5;208mDeseja realizar outra operacao?\033[0m" << endl
                                 << "\n\033[38;5;208mDigite 's' para realizar outra operacao ou qualquer outra letra ou numero caso queira encerrar o sistema! \033[0m" << endl;
                            
                            cin >> resposta;
                            cin.ignore();
                            busca_valida = true;
                        } 
                        else {
                            ordenarESalvar(dadosPessoas.data(), numRegistros, true);
                            editar_usuario_CPF(dadosPessoas.data(), numRegistros);

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
                qtd_imprimir(dadosPessoas.data(), numRegistros);
                cout << "\n\033[38;5;208mDeseja realizar outra operacao?\033[0m" << endl
                     << "\n\033[38;5;208mDigite 's' para realizar outra operacao ou qualquer outra letra ou numero caso queira encerrar o sistema! \033[0m" << endl;

                cin >> resposta;
                cin.ignore();
            } 
            else if (strcmp(opcao, "6") == 0) {
                ordenarESalvar(dadosPessoas.data(), numRegistros, false);
                opcao_valida = false;
                resposta = 'n';
            }
        } 
    } while (opcao_valida && (resposta == 's' || resposta == 'S'));
    
    ordenarESalvar(dadosPessoas.data(), numRegistros, false);

    cout << "\033[1;32mObrigado por usar nosso sistema! Ate logo.\033[0m" << endl;

    return 0;
}
