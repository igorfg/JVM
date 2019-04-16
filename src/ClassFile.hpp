#ifndef CLASSLOADER_H_INCLUDED
#define CLASSLOADER_H_INCLUDED

#include <cstdint>
#include <vector>

using namespace std;

#define MAGIC_NUMBER 0xCAFEBABE;

/*Declarado public, pode ser acessado de fora do pacote*/
#define ACC_PUBLIC 0x0001;
/*Declarado final, subclasses nao sao permitidas*/
#define ACC_FINAL 0x0010;
/*Trata metodos da superclasse especialmente quando invocados pela instrução invokespecial*/
#define ACC_SUPER 0x0020;
/*Eh uma interface, nao uma classe.*/
#define ACC_INTERFACE 0x0200;
/*Declarado abstract, nao deve ser instanciado*/
#define ACC_ABSTRACT 0x0400
/*Declarado synthetic, nao deve apresentar codigo fonte*/
#define ACC_SYNTHETIC 0x1000
/*Declarado como tipo annotation*/
#define ACC_ANNOTATION 0x2000
/*Declaram como tipo enum*/
#define ACC_ENUM 0x4000

class ClassFile {
private:
    /* magic eh o identificador do arquivo .class. Seu valor deve corresponder a 0xCAFEBABE */
    uint32_t magic;

    /* minor e major correspondem a versao do arquivo class. Ex: M = 2 e m = 1 => versao eh 2.1 */
    uint16_t minorVersion;
    uint16_t majorVersion;

    /* Constant pool count eh o numero de entradas na constant pool table + 1*/
    uint16_t constantPoolCount;

    /*
    constantPool eh uma tabela de structs representando varias constantes string, nomes de interfaces e classes, nomes de fields
    e outras constantes que sao referenciadas dentro da struct ClassFile e suas substructs. O formato de cada entrada da tabela constantPool
    eh indicada pelo byte "tag".

    A tabela constantPool eh indexada de 1 a constantPoolCount-1.
    */
    //vector<CPInfo> constantPool;

    /* O valor de accessFlags eh a mascaraca de flags usadas para denotar
       as permissões de acesso e propriedades da classe ou interface.
    */ 
    uint16_t accessFlags;

    /* O valor de thisClass deve ser um indice valido na constantPoolTable.
       A entrada naquele indice deve ser uma CONSTANT_Class_info structure que
       representa a classe ou interface definida por esse arquivo .class
    */
    uint16_t thisClass;

    /* Para uma classe, o valor de superClass deve ser zero ou deve ser um indice valido na constantPoolTable.
       Se o valor nao for zero, a entrada na tabela naquele indice deve ser uma CONSTANT_Class_info structure
       representando a superclasse direta da classe definida nesse .class. Nem a superclasse direta nem nenhuma
       de suas superclasses deve ter a flag ACC_FINAL setada em sua accessFlags na estrutura de seu ClassFile.
       Se o valor da superClass for zero, entao essa classe deve representar a classe Object, a unica classe ou
       interface sem uma superclasse direta.
       Para uma interface, o valor de superClass sempre deve ser um indice valido na tabela constantPool. A entrada
       no índice deve ser uma CONSTANT_Class_info strucure representndo a classe Object.
    */
    uint16_t superClass;

    /*O valor de interfacesCount da o numero de superinterfaces diretas dessa classe ou interface*/
    uint16_t interfacesCount;

    /*
    Cada valor no array interfaces deve ser um indice valido na tabela constantPool.
    A entrada na tabela denotada peols indices de interfaces[i], onde 0 <= i < interfacesCount
    deve conter uma CONSTANT_Class_info structure representando uma interface que eh uma superinterface direta dessa classe ou interface
    na ordem da esquerda para direita dada no fonte do tipo.
    */
    vector<uint16_t> interfaces;

    /*O valor de fieldsCount da o numero de FieldInfo strcutures na tabela de fields. As FieldInfo structures representam
      todos os camposm varuaveus de classe e de instancia declarados por essa classe ou interface    
    */
    uint16_t fieldsCount;

    /*
    Cada valor na tabela fields deve conter uma FieldInfo strucuture dando uma descricao completa de um field nessa classe ou interface.
    A tabela de fields inclui apenas os campos que sao declarados por essa classe ou interface. Nao inclui itens representando campos que
    sao herdados por superclasses ou superinterfaces.
    */
    //vector<FieldInfo> fields;

    /*
    O valor de methodsCount da o numero de MethodInfo structures na methods table.
    */
    uint16_t methodsCount;

    /*
    Cada valor na tabela methods deve conter uma struct MethodInfo dando uma completa descriccao de uma metodo nessa classe ou interface.
    Se nenhuma das flags ACC_NATIVE e ACC_ABSTRACT estiverem ativadas em accessFlags de uma struct MethodInfo, entao as instricuoes da JVM
    implementando e sse metodo tambem sao fornecidas.

    Structs MethodInfo representam todos os metodos declarados por essa classe ou interface, incluindo metodos de instancia, metodos de classe,
    metodos de inicializacao de instancia e qualquer metodo de inicializacao de classe ou interface.
    A methodsTable nao inclui itens representando metodos que sao herdados de superclasses ou superinterfaces.
    */
    //vector<MethodInfo> methods;

    /*O valor de attributesCount da o numero de atributos na tabela de atributos dessa classe*/
    uint16_t attributesCount;

    /*
    Cada valor na tabela de atributos deve ser uma struct AttributeInfo.
    */
    //vector<AttributeInfo> attributes;

};


#endif