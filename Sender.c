#include <winsock2.h>
#include "ByteArray.h"
#include "Declarations.h"

ByteArray TMP=NULL;
//static char* msg="salut";

void sendPacket(SOCKET sock, int id, byte* content, int size)
{
    ByteArray this;
    switch (id)
    {
    case 3 : { this=createIdentificationMessage(content,size); id=4; break; } // identifiants cryptés
    case 6469 : { TMP=createAuthentificationTicketMessage(content,size); return; } // récupération de l'ip du serveur et du ticket
    case 101 : { this=TMP; id=110; break; } // envoi du ticket
    case 6253 : { this=sendAntiBot(content,size); id=851; break; } // lire le rawdata et envoyer un MP au serveur
    case 6267 : { this=createCharactersListRequestMessage(); id=150; break; } // demande des persos
    case 151 : { this=createCharacterSelectionMessage(content,size); id=152; break; } // choix du perso
    case 6471 : { this=createClientKeyMessage(); id=5607; break; } // clé client
    case 6316 : { this=createSequenceNumberMessage(); id=6317; break; } // séquence
    case 220 : { this=createMapInformationsRequestMessage(content,size); id=225; break; } // demande d'informations sur la map
    case 30 : { writeIntoLog("Serveur de jeu indisponible.\n"); exit(0); } // maintenance
    case 6362 : { readBasicAckMessage(content,size); return; }
    //case 5632 : { TMP=createChatClientPrivateMessage(content, size, msg, strlen(msg)); return; } // message privé
    case 6454 :
        {
            this=TMP;
            TMP=NULL;
            id=851;
            if(this!=NULL)
                break;
            return;
        }
    default : return;
    }
    send(sock, (char*)getBuffer(this), getPosition(this),0);
    writeIntoLog("Envoi du paquet %d (%s)\n",id,printPacketName(id));
    writeIntoLog("Taille : %d octets\n\n",getPosition(this));
    detruireByteArray(this);
}
