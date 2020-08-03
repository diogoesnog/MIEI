package code;

import org.apache.commons.lang3.StringUtils;

import java.io.*;
import java.security.*;
import java.security.cert.Certificate;
import java.security.cert.CertificateException;
import java.security.cert.CertificateFactory;
import java.util.Arrays;
import java.util.Scanner;

import wsdlservice.*;

/**
 * Classe usada gerir o teste dos vários comandos que permitem executar as operações do SOAP Server.
 * Trata a informação vinda do Input do Terminal, retornando o resultado final para o mesmo.
 * @author Diogo Araújo
 * @author Diogo Nogueira
 * @version 1.0
 */
public class CmdSoapMsg {

    // Estabelecer a ligação ao Web Service SOAP
    final CCMovelDigitalSignature service = new CCMovelDigitalSignature();
    final CCMovelSignature connector = service.getBasicHttpBindingCCMovelSignature();

// --Commented out by Inspection START (06/07/2020 22:42):
//    /**
//     * Função que trata de retornar o URL WSDL a usar para criar o Web Service SOAP
//     * @param wsdl Número do URL
//     * @return URL WSDL
//     */
//    public String getWsdl(int wsdl) {
//
//        String[] wsdlURL = new String[] {
//                "https://preprod.cmd.autenticacao.gov.pt/Ama.Authentication.Frontend/CCMovelDigitalSignature.svc?wsdl",
//                "https://cmd.autenticacao.gov.pt/Ama.Authentication.Frontend/CCMovelDigitalSignature.svc?wsdl"
//        };
//        try {
//            return wsdlURL[wsdl];
//        } catch(ArrayIndexOutOfBoundsException exception) {
//            return "No valid WSDL.";
//        }
//    }
// --Commented out by Inspection STOP (06/07/2020 22:42)

    /**
     * Função que cria uma Hash SHA256 da Mensagem passada como parâmetro
     * @param message Texto à qual se quer aplicar a Hash
     * @return Hash do Conteúdo do Texto
     */
    public byte[] hash(String message) {

        MessageDigest digest;
        try {
            digest = MessageDigest.getInstance("SHA-256");
            return digest.digest(message.getBytes());
        } catch (NoSuchAlgorithmException e) {
            System.out.println("Can't find SHA256 Algorithm.");
            System.exit(0);
            return null;
        }
    }

    /**
     * Função que trata de criar um PEM File com a Chain de Certificados do Utilizador
     * @param applicationId Application Id dada (ou não) como argumento
     * @param userId User Id que será usado para o nome do ficheiro PEM
     */
    public void createPemFile(byte[] applicationId, String userId) {

        String certificate = getCertificate(applicationId,userId);
        OutputStream certificatePem = null;

        try {
            certificatePem = new FileOutputStream(new File("src/main/resources/" + StringUtils.substring(userId,5) + ".pem"));
            certificatePem.write(certificate.getBytes(), 0, certificate.length());
        } catch (IOException exception) {
            System.out.println("Unable to create PEM File.");
        } finally {
            try {
                assert certificatePem != null;
                certificatePem.close();
            } catch (IOException exception) {
                System.out.println("Unable to close PEM File.");
            }
        }
    }

    /**
     * Função que trata de criar um KeyStore com a Chain dos Certificados do Utilizador
     * @param userId User Id a usar para saber qual ficheiro PEM deve ser aberto/lido
     * @return Uma variável contendo o chain de certificados
     */
    public KeyStore getCertChain(String userId) {

        String aliasName = null;
        int numberPath = 0;

        InputStream pemFile = null;
        try {
            pemFile = new FileInputStream("src/main/resources/" + StringUtils.substring(userId,5)  + ".pem");
        } catch (FileNotFoundException e) {
            System.out.println("Unable to open the file.");
            System.exit(0);
        }
        BufferedInputStream contentPemFile = new BufferedInputStream(pemFile);
        CertificateFactory cf = null;
        try {
            cf = CertificateFactory.getInstance("X.509");
        } catch (CertificateException e) {
            System.out.println("Can't find X.509 Algorithm.");
            System.exit(0);
        }

        KeyStore keyStore = null;
        try {
            keyStore = KeyStore.getInstance(KeyStore.getDefaultType());
            keyStore.load(null);

            while (contentPemFile.available() > 0) {
                if(numberPath == 0) aliasName = "user";
                else if(numberPath == 1) aliasName = "root";
                else if(numberPath == 2) aliasName = "CA";

                Certificate certificate = cf.generateCertificate(contentPemFile);
                keyStore.setCertificateEntry(aliasName, certificate);

                numberPath++;
            }
        } catch (KeyStoreException | NoSuchAlgorithmException e) {
            System.out.println("Impossible to parse to load the Key Store.");
            System.exit(0);
        } catch (CertificateException | IOException e) {
            System.out.println("Can't generate X.509 Certificate.");
            System.exit(0);
        }

        return keyStore;
    }

    /**
     * Função que trata de obter informações referentes ao Subject do Certificado do Utilizador
     * @param certChain KeyStore com a Chain dos Certificados do Utilizador
     * @param aliasName Alias Name do Certificado ao qual se quer retirar as informações
     * @return Uma String com o Subject pedido
     */
    public String getSubject(KeyStore certChain, String aliasName) {

        String certificate = null;
        try {
            certificate = certChain.getCertificate(aliasName).toString();
        } catch (KeyStoreException e) {
            System.out.println("Can't get the Certificate with that Alias Name.");
            System.exit(0);
        }

        return StringUtils.substringBetween(certificate, "Subject: CN=", ",");
    }

    /**
     * Função que trata de obter o Certificado do Utilizador
     * @param applicationId Application Id dada (ou não) como argumento
     * @param userId Id do Utilizador
     * @return Uma String com o Certificado do Utilizador
     */
    public String getCertificate(byte[] applicationId, String userId) {
        return connector.getCertificate(applicationId, userId);
    }

    /**
     * Função que trata de invocar a operação CCMovelSign do Web Service SOAP
     * @param applicationId Application Id dada (ou não) como argumento
     * @param docName Nome do Documento a assinar
     * @param hash Hash a usar na assinatura
     * @param userId Id do Utilizador
     * @param userPin Pin do Utilizador
     * @return Uma String com o Process Id do pedido de Assinatura
     */
    public String ccMovelSign(byte[] applicationId, String docName, byte[] hash, String userId, String userPin) {

        // Criar a Instância do Pedido
        SignRequest request = new SignRequest();

        // Definir o Application Id
        request.setApplicationId(applicationId);

        // Definir o Document Name
        if(docName == null) request.setDocName("Documento Teste");
        else request.setDocName(docName);

        // Definir a Hash
        if(hash == null) {
            String message = "Nobody inspects the spammish repetition";
            byte[] encodedHash = hash(message);
            request.setHash(encodedHash);
        }
        else {
            request.setHash(hash);
        }

        // Definir o Id e o Pin do User
        request.setUserId(userId);
        request.setPin(userPin);

        // Efetuar o pedido ao serviço AMA
        SignStatus status = connector.ccMovelSign(request);

        // Retornar apenas o processID para mostrar no menu CLI
        return status.getProcessId();
    }

    /**
     * Função que trata de invocar a operação CCMovelMultipleSign do Web Service SOAP
     * @param applicationId Application Id dada (ou não) como argumento
     * @param userId Id do Utilizador
     * @param userPin Pin do Utilizador
     * @return Uma String com o Process Id do pedido de Assinatura
     */
    public String ccMovelMultipleSign(byte[] applicationId, String userId, String userPin) {

        // Criar a Instância do Pedido
        MultipleSignRequest request = new MultipleSignRequest();

        // Definir o Application Id
        request.setApplicationId(applicationId);

        // Definir o Id e o Pin do User
        request.setUserId(userId);
        request.setPin(userPin);

        // Definir o Array de Documentos a Assinar
        ArrayOfHashStructure documents = new ArrayOfHashStructure();

        // Documento 1
        HashStructure firstDocument = new HashStructure();

        String firstMessage = "Nobody inspects the spammish repetition";
        byte[] firstHash = hash(firstMessage);

        firstDocument.setHash(firstHash);
        firstDocument.setName("Docname Test 1");
        firstDocument.setId("1234");

        documents.getHashStructure().add(firstDocument);

        // Documento 2
        HashStructure secondDocument = new HashStructure();

        String secondMessage = "Nobody inspects the spammish repetition";
        byte[] secondHash = hash(secondMessage);

        secondDocument.setHash(secondHash);
        secondDocument.setName("Docname Test 2");
        secondDocument.setId("1235");

        documents.getHashStructure().add(secondDocument);

        // Efetuar o pedido ao serviço AMA
        SignStatus status = connector.ccMovelMultipleSign(request, documents);

        // Retornar apenas o processID para mostrar no menu CLI
        return status.getProcessId();
    }

    /**
     * Função que trata de validar o OTP recebido pelo Utilizador
     * @param applicationId Application Id dada (ou não) como argumento
     * @param processId Process Id recebido na operação CCMovelSign/CCMovelMultipleSign
     * @param otpCode OTP Code recebido pelo Utilizador
     * @return Um Array de Bytes com a Assinatura do Documento
     */
    public byte[] validateOtp(byte[] applicationId, String processId, String otpCode) {

        SignResponse response = connector.validateOtp(otpCode, processId, applicationId);

        // Imprimir o resultado da validação da assinatura
        System.out.println(response.getStatus().getMessage());

        // Retornar a assinatura para o menu CLI
        return response.getSignature();
    }

    /**
     * Função que executa sequencialmente todas as operações anteriores
     * @param applicationId Application Id dada (ou não) como argumento
     * @param docName Nome do Documento a assinar
     * @param userId Id do Utilizador
     * @param userPin Pin do Utilizador
     * @return Uma String com o resultado de toda a execução/validação do programa e da assinatura
     */
    public String testAll(byte[] applicationId, String docName, String userId, String userPin)  {

        // Inicialização Test All Commands
        System.out.println("Test Command Line Program (for Preprod/Prod Signature CMD (SOAP) version 1.6 technical specification)");
        System.out.println("Initializing Test of All Commands");

        // Leitura dos Argumentos da Linha de Comandos
        System.out.println("0% ...   Reading Arguments from the Command Line");
        System.out.println("         Document Name: " + docName + ", User Id: " + userId);

        // Obtenção do Certificado e da KeyStore com a Chain do Certificado
        System.out.println("10% ...  Contacting CMD SOAP Server for GetCertificate Operation");

        createPemFile(applicationId, userId);
        KeyStore certChain = getCertChain(userId);

        // Impressão das informações dos vários níveis da Chain do Certificado
        System.out.println("20% ...  Certificate Emitted for " + "\"" + getSubject(certChain, "user") + "\"");
        System.out.println("         by the Certification Entity " + "\"" + getSubject(certChain, "CA") + "\"");
        System.out.println("         in the Hierarchy of " + "\"" + getSubject(certChain, "root") + "\"");

        // Leitura do Documento
        System.out.println("30% ...  Reading the Document " + "\"" + docName + "\"");

        FileInputStream document = null;
        try {
            document = new FileInputStream(new File("src/main/resources/" + docName));
        } catch (IOException exception) {
            System.out.println("Unable to open Document " + "\"" + docName + "\"");
        } finally {
            try {
                assert document != null;
                document.close();
            } catch (IOException exception) {
                System.out.println("Unable to close Document " + "\"" + docName + "\"");
            }
        }
        BufferedInputStream contentDocument = new BufferedInputStream(document);

        // Criação Hash do Documento
        System.out.println("40% ...  Hashing the Document " + "\"" + docName + "\"");

        byte[] hashDocument = hash(contentDocument.toString());

        // Impressão da Hash
        System.out.println("50% ...  Generated Hash ");
        System.out.println("         " + Arrays.toString(hashDocument));

        // Contactar Servidor SOAP para a operação CCMovelSign
        System.out.println("60% ...  Contacting CMD SOAP Server for CCMovelSign Operation");
        String resultCcMovelSign = ccMovelSign(applicationId, docName, hashDocument, userId, userPin);

        // Impressão do Process Id devolvido na operação anterior
        String processId = StringUtils.substringBefore(resultCcMovelSign, "ValidateOTP\n");
        System.out.println("70% ...  Process Id returned by CCMovelSign Operation");
        System.out.println("         " + processId);

        // Validação da OTP
        Scanner myScanner = new Scanner(System.in);
        System.out.println("80% ...  Initializing OTP Validation\n");
        System.out.println("Enter the OTP received on your Device:");
        String otpCode = myScanner.nextLine();

        System.out.println("90% ...  Contacting CMD SOAP Server for ValidateOtp Operation");
        byte[] signature = validateOtp(applicationId, processId, otpCode);

        // Validação da Assinatura devolvida pela operação anterior
        System.out.println("100% ... Signature returned by ValidateOtp Operation");
        System.out.println("         " + Arrays.toString(signature));

        System.out.println("110% ... Validating Signature\n");

        // Digest a verificar com a chave pública RSA
        byte[] hashFile = hash(contentDocument.toString());

        // Inicializar a verficação da assinatura RSA com o certificado do user
        Signature sig = null;
        try {
            sig = Signature.getInstance("NonewithRSA");
        } catch (NoSuchAlgorithmException e) {
            System.out.println("Can't get the RSA Algorithm.");
            System.exit(0);
        }
        try {
            PublicKey pubkey = certChain.getCertificate("user").getPublicKey();
            assert sig != null;
            sig.initVerify(pubkey);
            sig.update(hashFile);
            if (sig.verify(signature)) {
                System.out.println("Assinatura verificada com sucesso.");
            }
            else {
                System.out.println("Este certificado de utilizador não assinou este documento.");
            }
        } catch (InvalidKeyException | SignatureException e) {
            System.out.println("The verification of the signature failed.");
            System.out.println(e.toString());
        } catch (KeyStoreException e) {
            System.out.println("Can't get the Public Key from Certificate.");
            System.exit(0);
        }

        return "\n############################################ Test All Done ##############################################\n";
    }

}
