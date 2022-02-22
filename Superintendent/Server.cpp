#include <chrono>
#include <cstdio>
#include "Server.hpp"

#define SERVER_CERT_FILE "./cert.pem"
#define SERVER_PRIVATE_KEY_FILE "./key.pem"

const char* Xbl_Ticket = "{\"user_id\":\"f9ed4a7d36ac51b7324d6d76738c0962\",\"refresh_token\":\"M.R3_BL2.-CY*LNjZCdXblxILwYv!tQ2s3FDabGIR9ZYEJ!jlbXI*83RADwodHNMFbrjLhcEKB0XbxxTUMKKltTWAk4IHGGP7oz6q6aYbXGiUQANZDhpAJVYBfckXzSx*TJDW4C3nSkWAyFhAwztQd0LrDuI7K39LiVW5uK4lgQbt7dISzFKpC*gzHLWl9pappUNOXZpWJWt!WY0s*FWKr0cNcRQ5XI3SudMXxiUrwxi7qc2uUIVCdRUNslIByEzu5Gi2wHtyud7SVRmd!0ssMcjZsEdUOfkL0Go*Z102nQXM4IO0g1fg*SSqhLBLT7CkoKUB3jWLPDg$$\",\"foci\":\"\",\"access_tokens\":[{\"access_token\":\"d=EwDwAupvBAAUKods63Ys1fGlwiccIFJ+qE1hANsAASoWCW93RgMMo8ZEdx7HtPWCix05QpVTme3E1pkTwmKlzy5kZFctmD2qYVFndlsiaLSiS8w9euT1GWUYNajQ5EgRpPgWF0fiLe029myeA0HkxA28RWjWOtDYIlcY/oCiXyVxbQUGwpxY0kX/2skpznUztmrznxlYO9AzGg8tc7Mlhh/e6tR82bR+eRAWUh0/T7uZmA7YdBDHnyh6/ogaRespmfjmWBMcsmJndFjyiLHDfPKqLk0pd8NtwSOTvdfeQ4Ai9FtNLd+GIFzKJ909JPUekbgVRBKGNM8er8Nl9If8QHvM/0sz4cAQa/5iQyYULWBAw3V/g9f87YfMRWPXXngDZgAACLKfG/E2gYh9wAEK35F99rADaXBUqP3buQsEv19yNnuw9fd6eBxjER0akcZKvYEKQ/am6GZ4xR6+wz3S3gheoKN8W9MGcZhNZxjacIk188ELzt3FAQPyt1kXMQzTvv4/0HFdjHWQsVfAkGrb03Clxti/ooKAAdq+bPQX8R3UMcopgUtR40KSZngk/j1JJHoAUlPi6uZOh0ywNZIpIBT3kAjjEl2auw7Ba9ZEruiIVAcIbKSGJQvt5QSPatmPxJuGXEQbN13t45KImnav9q7Wa6PLL1tK2yuZ/qGeGeDXcWRAitd890MDTnhdSLldb0qOy/Q6sjP7f5DjDH4Z45NveK83MSMKGwmC67eCi3Ulrdb/f48Q8G8PH5cHNMcbHxAO1DvT4vnpH9hwxIjwHyVjqJSb3dW3h1MgnwlO9+OYtdYRH2lHFPdd8r+ARYlEujxImDLebZYFi7mhn+LxYMRuXUMp/7GMCVVOvL7RJxFmozt8o8JisJ5iptUwEpG59emhyZQ+HBYwzzR9cuMBwIQNzlE8YT/Wf/A8jasL9YDO4RRlpnCcJ8WGqwkMOUOYHtZ5Lfeovx+0YmsjCfZTwCtt7UbwQSegJul33SAiBgI=\",\"xal_expires\":\"2099-02-18T03:19:02.4320000Z\",\"scopes\":\"xboxlive.signin\"}]}";
const char* Xbl1 = "{\"MsaUserId\":\"f9ed4a7d36ac51b7324d6d76738c0962\",\"HasSignInDisplayClaims\":true,\"IdentityType\":\"Xtoken\",\"Environment\":\"Production\",\"Sandbox\":\"RETAIL\",\"TokenType\":\"JWT\",\"RelyingParty\":\"http://xboxlive.com\",\"SubRelyingParty\":\"\",\"TokenData\":{\"Token\":\"eyJlbmMiOiJBMTI4Q0JDK0hTMjU2IiwiYWxnIjoiUlNBLU9BRVAiLCJjdHkiOiJKV1QiLCJ6aXAiOiJERUYiLCJ4NXQiOiIxZlVBejExYmtpWklFaE5KSVZnSDFTdTVzX2cifQ.dN_p_a8IJ3g-2muEvrtVLTtuwNp2VvYwHeiEXtRe5unIyoMdPfKghlaWLhUWYx46E0A6JqTqtOtUueNKpYyjM1OKoTt8laAG7aGJgyMqHz1AHltK9otBQODLOLnDvZJ1GO9KgBhEGT1bIjG7cHRrk4ZUYK1G9q1Xl89A228G9gU.Vde8nMafMVeV9LbO7vNqYQ.G2s_Iq1AspBfs_Bk4f_Bs0dMxMGCjQ4UwtT3GP-zo8AT1w40Jh-xrCPP4XlsfryXqMTcYlkcITtzY90b2mF_bquEmnc3m8d3ghGBW00InSGucSWrXeU3WtorZG2ld1aZjF9Wx8KddhPj5BTtXq8NRa7RdxN1_e962hmTZQEa6G9TXHUghj8PxpuRNzYlMzQ5382Ns0hr4OYatCOOAWf8ouU2O1Ml5_05oS-syCcnIOSHNv8QZFI25mFO2JOs8X0HEIArnNMQ98lCJqEuO1mbidAGSnlJKMyTrMwxz-5zEUrnoOn5xOn9cNg5sSAX7Cx5d2QI39YuavYKiBFj_Mmlej62UgwFf0r9tiiTa-AXXby8KqUuVqhPLEXLcACwMEPKRTEslj8pPz0m9JfnW4RgMgKYnLPxS3yTSkyZNeC7cvpEPTZ-gGUVHfAt4kPdNZ88PKsD3itY8zCMSD621Vp6U251j8Xjj5Fr6cRYh7Ah2QHn6ATwV2kmJmSnGcT5wCZP93uqUYgJCLgEYv1KzUb17L9ldTp1ZF2QfdehAE4zWKCQ7FZpISAS5VRNzhBQSZThLIKfyjrqHfpfFNifhgPl1Q6mOVs-tBn-32bKlkN6z0h2-Ut_5bV3a0LG2OtLdbwLb0hHi2gMq2bVQZiS7tVQZoaEFFhiT9xCq7HYztUFMnhpG3SD1FmGFyawgrUOJMP6-l33bCKSGcijHIiC5CaVsj-tR7gKw5yxmPDUxBVSOJaQdVRq-Y-MVQWMJqETzfscgw3LH5GidyjzmT9RAWYXQREvp0mvUcW04DY12H_YCLknV9yEvD-XugY5yc_yQUdvLOvvxBK6DTGgE0gsMH7vV9_IhZujfW1-ezj-wXnYn5nR-v1ni4BB2nA_Lch1uFo2V1ZiBVfqfTNASJfo5JhK1vRnjqyAiuwG3YKL3XEVqTiJJaQ8Qorh9VJHue0Hntxdej_V5fGhnJoude0VjWv8g207I0bBXC9llH2dQiFHOiChnul7XhQtPhvAV-VeDTt7dHRziz-aT5T24BcUxX0_ovCC1R6QuaCl5JxziUtNR-E8i9pRlpbn7eGR-ZcVd6mpJosKpxQw1hiTKGTor0w3AsT8WT-8qRp8cbZAZTbLGNXnHQ_epqmbdeY_SkSYZtb61ADW65wys0Wya_Y0Obrsipv3NWwqX6ekD2thHBFAqNwIpdpRWPhet0dFfZlRUGGO2t8K6InhiPGWrPN_bCPyJy7Dr3fMbNM3nEmlH6XKZ6Eqp3CY7dV0aO5MZrRMI5hH0FQLmLGZtCkPZuHAim8bKGeIbxzclEh6Co2inoHJLcrV5zEbKuSsT6ioniIRnOC9aRiOThmBr1_miisuTf97sEnCmiUHl_BLNggjxYPQhcELBELDEkTMf3142M3sy3tyN-eLHzPvF-1sCHr7N-m9_PrSR2uY46NIp-xfwa_1QVkBy-GvcefLCOk6bvXyZnzcWbaQINkrl98h9N-KFQCj2LT1gv8M8CIZCc_ZxebsF1Q7oJIwKXcxRMTZ5FTNWAVUCXdlpRDlmCrq_h04cd6KdLDpEBIaCp8A-5UyBpZFjOwtbEU5TaxaTcIZZiUwP2l2w-55LJl7JU14Exhj2dkrMb40jQQhrss6AQ86wSgtT1xqu7jILYDThvf94E3xVroWNPR6fuTg7xZjH8jEKQKpYInbfL0moleW7YwPJOtt5dFBwKIaYUsymKcR1ck4XiChQd5ctX3yH2esltjSU-WPqKcLCaqYugsDPj_coJwdTQSZS-dag2VESG0Xrnyharr3crYF9bKDOgF5q0cbpZ8Pw57FqP5jtyiXTwmJfD3EAwdufvyD8_jQ8OzW45DtS0ZTQMUG3rUfo3To8rgJABX7lrfZww8TPtnAa7a_QmUA_Z02gM1pDKhXlGFROSX32HRW.gNU9CERWaiT8nm4Yd6rYM7mBa0C13-KFwKl-W4DbSsU\",\"NotAfter\":\"2099-0";
const char* Xbl2 = "2-18T18:19:09.3920000Z\",\"IssueInstant\":\"2022-02-18T02:19:09.3920000Z\",\"ClientAttested\":false,\"DisplayClaims\":{\"xui\":[{\"uhs\":\"4522514856330333048\",\"gtg\":\"PublicEnv00\",\"mgt\":\"PublicEnv00\",\"mgs\":\"\",\"umg\":\"PublicEnv00\",\"xid\":\"2535467660435810\",\"agg\":\"Adult\",\"prv\":\"184 185 186 187 188 189 191 193 196 200 201 203 204 205 206 208 211 217 224 227 228 235 238 245 247 249 252 254 255\",\"usr\":\"195 234\",\"uer\":\"\",\"utr\":\"190 198 199 220\"}]}}}";
const char* Xbl_DeviceKey = "{\"Id\":\"{6C30DA2D-D5B0-4B40-9DCB-5C28E1E3428F}\",\"Key\":\"RUNTMiAAAADHfxP/hmEosi5iYVBkgJ+WOveWc0feHQ8IURTXLUpzRDjbEcpuDdVaye701N0W1jFoSFlGUy0+MPKgApmmahqwOoW33YEL+1+CK9JBHgSuOPknNpJbVO9R4c/Vr+sesYI=\"}";

bool isFirstRun = true;

std::string dump_headers(const Headers& headers)
{
    std::string s;
    char buf[BUFSIZ];

    for (auto it = headers.begin(); it != headers.end(); ++it)
    {
        const auto& x = *it;
        snprintf(buf, sizeof(buf), "%s: %s\n", x.first.c_str(), x.second.c_str());
        s += buf;
    }

    return s;
}

std::string log(const Request& req, const Response& res)
{
    std::string s;
    char buf[BUFSIZ];

    s += "================================\n";

    snprintf(buf, sizeof(buf), "%s %s %s", req.method.c_str(), req.version.c_str(), req.path.c_str());

    s += buf;

    std::string query;

    for (auto it = req.params.begin(); it != req.params.end(); ++it)
    {
        const auto& x = *it;

        snprintf(buf, sizeof(buf), "%c%s=%s", (it == req.params.begin()) ? '?' : '&', x.first.c_str(), x.second.c_str());

        query += buf;
    }

    snprintf(buf, sizeof(buf), "%s\n", query.c_str());

    s += buf;

    s += dump_headers(req.headers);

    s += "--------------------------------\n";

    snprintf(buf, sizeof(buf), "%d %s\n", res.status, res.version.c_str());

    s += buf;

    s += dump_headers(res.headers);

    s += "\n";

    if (!res.body.empty())
    {
        s += res.body;
    }

    s += "\n";

    return s;
}

std::vector<char> readFile(const char* filename)
{
    std::streampos fileSize;
    std::ifstream file(filename, std::ios::binary);

    file.seekg(0, std::ios::end);
    fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<char> fileData(fileSize);
    file.read((char*)&fileData[0], fileSize);
    return fileData;
}

void sendFile(Response& res, const char* filename, const char* type)
{
    std::vector<char> filedata = readFile(filename);

    res.set_content_provider(filedata.size(), type, [filedata](size_t offset, size_t length, DataSink& sink)
        {
            sink.write(filedata.data(), filedata.size());
            return true;
        },

        [filedata](bool success) {});
}

void WriteGenericCredential(const wchar_t* Target, const wchar_t* Comment, const char* Password)
{
    const char* password = Password;
    DWORD blobsize = strlen(password);

    CREDENTIAL cred = { 0 };
    cred.Flags = NULL;
    cred.Type = CRED_TYPE_GENERIC;
    cred.TargetName = (LPWSTR)Target;
    cred.Comment = (LPWSTR)Comment;
    cred.CredentialBlobSize = blobsize;
    cred.CredentialBlob = (LPBYTE)password;
    cred.Persist = CRED_PERSIST_LOCAL_MACHINE;
    cred.UserName = (LPWSTR)L"";

    if (!CredWrite(&cred, 0))
    {
        std::cerr << GetLastError() << std::endl;
    }
}

void ClearCredentials()
{
    if (!CredDelete(L"Xbl_Ticket|1840968352|Production|f9ed4a7d36ac51b7324d6d76738c0962", CRED_TYPE_GENERIC, 0))
    {
        std::cerr << GetLastError() << std::endl;
    }

    if (!CredDelete(L"Xbl|1840968352|f9ed4a7d36ac51b7324d6d76738c0962|Production|RETAIL|Xtoken|http://xboxlive.com||JWT", CRED_TYPE_GENERIC, 0))
    {
        std::cerr << GetLastError() << std::endl;
    }

    if (!CredDelete(L"Xbl|1840968352|f9ed4a7d36ac51b7324d6d76738c0962|Production|RETAIL|Xtoken|http://xboxlive.com||JWT|1", CRED_TYPE_GENERIC, 0))
    {
        std::cerr << GetLastError() << std::endl;
    }

    if (!CredDelete(L"Xbl|DeviceKey", CRED_TYPE_GENERIC, 0))
    {
        std::cerr << GetLastError() << std::endl;
    }

    if (!CredDelete(L"Xbl|1840968352|f9ed4a7d36ac51b7324d6d76738c0962|Production|RETAIL|Utoken|http://auth.xboxlive.com||JWT", CRED_TYPE_GENERIC, 0))
    {
        std::cerr << GetLastError() << std::endl;
    }
}

int main(void)
{
    SSLServer svr(SERVER_CERT_FILE, SERVER_PRIVATE_KEY_FILE);

    if (!svr.is_valid())
    {
        printf("Error: 101 \n");
        return -1;
    }

    if (isFirstRun == true)
    {
        ClearCredentials();
        WriteGenericCredential(L"Xbl_Ticket|1840968352|Production|f9ed4a7d36ac51b7324d6d76738c0962", L"{B35AEA94-E2C0-41BC-9BEA-704BA5FB4F77}|00000000|1", Xbl_Ticket);
        WriteGenericCredential(L"Xbl|1840968352|f9ed4a7d36ac51b7324d6d76738c0962|Production|RETAIL|Xtoken|http://xboxlive.com||JWT", L"{318B87A7-3821-4B93-98D2-C9383E6363F5}|00000000|2", Xbl1);
        WriteGenericCredential(L"Xbl|1840968352|f9ed4a7d36ac51b7324d6d76738c0962|Production|RETAIL|Xtoken|http://xboxlive.com||JWT|1", L"{318B87A7-3821-4B93-98D2-C9383E6363F5}|00000001|2", Xbl2);
        WriteGenericCredential(L"Xbl|DeviceKey", L"{04D465E7-1E30-455B-9342-86FBEA6EBCD8}|00000000|1", Xbl_DeviceKey);
        isFirstRun = false;
    }

    while (isFirstRun == false)
    {
        svr.Get("/", [=](const Request&, Response& res)
            {
                res.set_redirect("/hi");
            });

        svr.Get("/hi", [](const Request&, Response& res)
            {
                res.set_content("Ok!", "text/plain");
            });

        svr.Post("/MultiplayerServer/ListPartyQosServers", [](const Request&, Response& res)
            {
                sendFile(res, ".\\Cache\\Pre\\01.json", "text/plain");
            });

        svr.Get("/titles/default/endpoints", [](const Request&, Response& res)
            {
                sendFile(res, ".\\Cache\\Pre\\02.data", "text/plain");
            });

        svr.Post("/collect/v1", [](const Request&, Response& res)
            {
                sendFile(res, ".\\Cache\\Pre\\03.json", "text/plain");
            });

        svr.Post("/device/authenticate", [](const Request&, Response& res)
            {
                sendFile(res, ".\\Cache\\Pre\\04.json", "text/plain");
            });

        svr.Post("/authenticate", [](const Request&, Response& res)
            {
                sendFile(res, ".\\Cache\\Pre\\05.json", "text/plain");
            });

        svr.Post("/oauth20_token.srf", [](const Request&, Response& res)
            {
                sendFile(res, ".\\Cache\\Pre\\06.json", "text/plain");
            });

        svr.Post("/authorize", [](const Request&, Response& res)
            {
                sendFile(res, ".\\Cache\\Pre\\07.json", "text/plain");
            });

        svr.Post("/xsts/authorize", [](const Request&, Response& res)
            {
                sendFile(res, ".\\Cache\\Pre\\08.json", "text/plain");
            });

        svr.Get("/titles/current/endpoints", [](const Request&, Response& res)
            {
                sendFile(res, ".\\Cache\\Pre\\09.data", "text/plain");
            });

        svr.Post("/system/notifications/endpoints", [](const Request&, Response& res)
            {
                sendFile(res, ".\\Cache\\Pre\\10.json", "text/plain");
            });

        svr.Get("/global/scids/00000000-0000-0000-0000-00006dbaf2a0/data/Configuration/", [](const Request&, Response& res)
            {
                sendFile(res, ".\\Cache\\Pre\\11.json", "text/plain");
            });

        svr.Post(R"(/users/xuid.*)", [](const Request&, Response& res)
            {
                res.set_content("Ok!", "text/plain");
            });

        svr.Get("/connect", [](const Request&, Response& res)
            {
                res.status = 101;
            });

        svr.Get("/global/scids/00000000-0000-0000-0000-00006dbaf2a0/data/Configuration/ConfigV2.json,config", [](const Request&, Response& res)
            {
                sendFile(res, ".\\Cache\\Pre\\12.bin", "text/plain");
            });

        svr.Get("/settings/hi343pc/26fffa65-821b-4f1c-802e-43e24b1c22de", [](const Request&, Response& res)
            {
                sendFile(res, ".\\Cache\\Post\\01.x-bond-compact-binary", "text/plain");
            });

        svr.Post("/spartan-token", [](const Request&, Response& res)
            {
                sendFile(res, ".\\Cache\\Post\\02.x-bond-compact-binary", "text/plain");
            });

        svr.Get("/oban/flight-configurations/titles/hi343/audiences/RETAIL/active", [](const Request&, Response& res)
            {
                sendFile(res, ".\\Cache\\Post\\03.x-bond-compact-binary", "text/plain");
            });

        svr.Get(R"(/oban/flight-configurations/titles/hi343/audiences/RETAIL/players/xuid.*)", [](const Request&, Response& res)
            {
                sendFile(res, ".\\Cache\\Post\\04.x-bond-compact-binary", "text/plain");
            });

        svr.Get("/hi343/manifests/builds/6.10020.12700/game", [](const Request&, Response& res)
            {
                sendFile(res, ".\\Cache\\Post\\05.x-bond-compact-binary", "text/plain");
            });

        svr.Get("/hi343/projects/a9dc0785-2a99-4fec-ba6e-0216feaaf041", [](const Request&, Response& res)
            {
                sendFile(res, ".\\Cache\\Post\\06.x-bond-compact-binary", "text/plain");
            });

        svr.Get("/hi343/info/tags?flight=c1178956-c7c8-4860-a3a7-da5caa55faad", [](const Request&, Response& res)
            {
                sendFile(res, ".\\Cache\\Post\\07.x-bond-compact-binary", "text/plain");
            });

        svr.Get("/hi343/ugcGameVariants/1e8cd10b-1496-423b-8699-f98f6f5db67e/versions/4155142e-b867-4030-a8a0-d5f44f9dce60", [](const Request&, Response& res)
            {
                sendFile(res, ".\\Cache\\Gamemodes\\ugcGameVariant_Slayer.x-bond-compact-binary", "text/plain");
            });

        svr.Get("/hi343/engineGameVariants/1cfee22b-513f-418d-a1d7-2648f1a575e0/versions/c6bed044-bdab-4c6a-87ce-03700959d976", [](const Request&, Response& res)
            {
                sendFile(res, ".\\Cache\\Gamemodes\\engineGameVariant_Slayer.x-bond-compact-binary", "text/plain");
            });

        svr.Get("/ugcstorage/enginegamevariant/1cfee22b-513f-418d-a1d7-2648f1a575e0/c6bed044-bdab-4c6a-87ce-03700959d976/Default.bin", [](const Request&, Response& res)
            {
                sendFile(res, ".\\Cache\\Gamemodes\\Slayer.bin", "text/plain");
            });

        svr.Get("/hi343/maps/298d5036-cd43-47b3-a4bd-31e127566593/versions/e53ca277-4669-42e9-962a-6513cf2d1eac", [](const Request&, Response& res)
            {
                sendFile(res, ".\\Cache\\Maps\\engineMap_ctf_Bazaar.x-bond-compact-binary", "text/plain");
            });

        svr.Get("/ugcstorage/map/298d5036-cd43-47b3-a4bd-31e127566593/e53ca277-4669-42e9-962a-6513cf2d1eac/ctf_bazaar.mvar", [](const Request&, Response& res)
            {
                sendFile(res, ".\\Cache\\Maps\\ctf_Bazaar.mvar", "text/plain");
            });

        svr.Get("/hi343/maps/53136ad9-0fd6-4271-8752-31d114b9561e/versions/d21e94a4-2f36-4799-9610-d78325683f45", [](const Request&, Response& res)
            {
                sendFile(res, ".\\Cache\\Maps\\engineMap_va_Behemoth.x-bond-compact-binary", "text/plain");
            });

        svr.Get("/ugcstorage/map/53136ad9-0fd6-4271-8752-31d114b9561e/d21e94a4-2f36-4799-9610-d78325683f45/va_behemoth.mvar", [](const Request&, Response& res)
            {
                sendFile(res, ".\\Cache\\Maps\\va_Behemoth.mvar", "text/plain");
            });

        svr.Get("/hi343/maps/4f196016-0101-4844-8358-2504f7c44656/versions/6e5ad39c-7280-4058-9f09-1825d942f48e", [](const Request&, Response& res)
            {
                sendFile(res, ".\\Cache\\Maps\\engineMap_btb_Fragmentation.x-bond-compact-binary", "text/plain");
            });

        svr.Get("/ugcstorage/map/4f196016-0101-4844-8358-2504f7c44656/6e5ad39c-7280-4058-9f09-1825d942f48e/btb_fragmentation.mvar", [](const Request&, Response& res)
            {
                sendFile(res, ".\\Cache\\Maps\\btb_Fragmentation.mvar", "text/plain");
            });

        svr.Get("/hi343/maps/b6aca0c7-8ba7-4066-bf91-693571374c3c/versions/a7e79f60-cfa1-4f3e-a004-aeb46b5bb62f", [](const Request&, Response& res)
            {
                sendFile(res, ".\\Cache\\Maps\\engineMap_sgh_Interlock.x-bond-compact-binary", "text/plain");
            });

        svr.Get("/ugcstorage/map/b6aca0c7-8ba7-4066-bf91-693571374c3c/a7e79f60-cfa1-4f3e-a004-aeb46b5bb62f/sgh_interlock.mvar", [](const Request&, Response& res)
            {
                sendFile(res, ".\\Cache\\Maps\\sgh_Interlock.mvar", "text/plain");
            });

        svr.Get("/hi343/maps/8420410b-044d-44d7-80b6-98a766c8c39f/versions/fd838d41-41be-4de7-9c2a-91b3551b37f9", [](const Request&, Response& res)
            {
                sendFile(res, ".\\Cache\\Maps\\engineMap_sgh_Blueprint.x-bond-compact-binary", "text/plain");
            });

        svr.Get("/ugcstorage/map/8420410b-044d-44d7-80b6-98a766c8c39f/fd838d41-41be-4de7-9c2a-91b3551b37f9/sgh_blueprint.mvar", [](const Request&, Response& res)
            {
                sendFile(res, ".\\Cache\\Maps\\sgh_Blueprint.mvar", "text/plain");
            });

        svr.Get("/ugcstorage/map/298d5036-cd43-47b3-a4bd-31e127566593/a5582547-29fb-4ceb-ac9d-74f899901501/images/hero.png", [](const Request&, Response& res)
            {
                sendFile(res, ".\\Cache\\Images\\ctf_Bazaar.png", "text/plain");
            });

        svr.Get("/ugcstorage/map/53136ad9-0fd6-4271-8752-31d114b9561e/1d62423c-39ad-4029-9db2-aab60ef664f1/images/hero.png", [](const Request&, Response& res)
            {
                sendFile(res, ".\\Cache\\Images\\va_Behemoth.png", "text/plain");
            });

        svr.Get("/ugcstorage/map/4f196016-0101-4844-8358-2504f7c44656/b7a5f610-4a9c-49de-85f0-2e9aa81193a3/images/hero.png", [](const Request&, Response& res)
            {
                sendFile(res, ".\\Cache\\Images\\btb_Fragmentation.png", "text/plain");
            });

        svr.Get("/ugcstorage/map/b6aca0c7-8ba7-4066-bf91-693571374c3c/c63ee410-784e-46ae-911e-ab7bc35933b1/images/hero.png", [](const Request&, Response& res)
            {
                sendFile(res, ".\\Cache\\Images\\sgh_Interlock.png", "text/plain");
            });

        svr.Get("/ugcstorage/map/8420410b-044d-44d7-80b6-98a766c8c39f/068c0974-f748-41ba-b457-b8fed603576e/images/hero.png", [](const Request&, Response& res)
            {
                sendFile(res, ".\\Cache\\Images\\sgh_Blueprint.png", "text/plain");
            });

        svr.Get("/ugcstorage/map/33c0766c-ef15-48f8-b298-34aba5bff3b4/8de91561-b9f7-4669-97ef-42e65fb507a7/images/hero.png", [](const Request&, Response& res)
            {
                sendFile(res, ".\\Cache\\Images\\Error.png", "text/plain");
            });

        svr.Get("/ugcstorage/map/56a11b8c-64d1-4537-8893-a9241e4d5b93/7804214e-c463-49e9-b269-d22694142916/images/hero.png", [](const Request&, Response& res)
            {
                sendFile(res, ".\\Cache\\Images\\Error.png", "text/plain");
            });

        svr.Get("/ugcstorage/map/f0a1760f-0d4a-4bcc-ac7a-e8f9aee331dc/6e9da6f4-fb07-4d38-b26e-2136941d5531/images/hero.png", [](const Request&, Response& res)
            {
                sendFile(res, ".\\Cache\\Images\\Error.png", "text/plain");
            });

        svr.Get("/ugcstorage/map/c494ef7c-d203-42a9-9c0f-b3f576334501/e7b22fbf-c768-43db-8fc7-9a5ac5ccc7d6/images/hero.png", [](const Request&, Response& res)
            {
                sendFile(res, ".\\Cache\\Images\\Error.png", "text/plain");
            });

        svr.Get("/ugcstorage/map/08607bf4-6abe-4a5b-9547-290a6cc1433e/0030c1e3-d8b2-4b60-a060-4873d8f4d4a2/images/hero.png", [](const Request&, Response& res)
            {
                sendFile(res, ".\\Cache\\Images\\Error.png", "text/plain");
            });

        svr.set_error_handler([](const Request&, Response& res)
            {
                const char* fmt = "<p>Error Status: <span style='color:red;'>%d</span></p>";
                char buf[BUFSIZ];
                snprintf(buf, sizeof(buf), fmt, res.status);
                res.set_content(buf, "text/html");
            });

        svr.set_logger([](const Request& req, const Response& res)
            {
                printf("%s", log(req, res).c_str());
            });

        svr.listen("anvillocalhost.com", 443);
    }

    return 0;
}