// classe que decidi criar pra criar uma solução diferente para 
// o som quando o alien morre ou qualquer outro efeito
// que envolva um som diferente

#ifndef SOUND_EFECT_H
#define SOUND_EFECT_H

class SoundEfect : public Sound{
public:
    SoundEfect(GameObject& associated, std::string file);
    void Update(float dt) override;
};

#endif // SOUND_EFECT_H