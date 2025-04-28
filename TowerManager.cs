using UnityEngine;
using UnityEngine.UI;
using TMPro;
using System.Collections.Generic;

public class TowerManager : MonoBehaviour
{
    [Header("Tower Settings")]
    [SerializeField] private GameObject blockPrefab;
    [SerializeField] private float spawnOffset = 2f;
    [SerializeField] private float swayForce = 1f;
    [SerializeField] private float maxTiltAngle = 30f;

    [Header("UI")]
    [SerializeField] private Button replayButton;
    [SerializeField] private TextMeshProUGUI scoreText;
    [SerializeField] private TextMeshProUGUI gameOverText;

    [Header("Camera Settings")]
    [SerializeField] private Camera mainCamera;
    [SerializeField] private float cameraHeightOffset = 10f;  
    [SerializeField] private float cameraFollowSpeed = 1f;  

    private List<GameObject> towerBlocks = new List<GameObject>();
    private bool gameOver = false;
    private int score = 0;

    private void Start()
    {
        replayButton.onClick.AddListener(ResetGame);
        gameOverText.gameObject.SetActive(false);
        SpawnBaseBlock();
        UpdateScore();
    }

    private void Update()
    {
        if (gameOver) return;

        HandleTouchInput();
        ApplyTowerSway();
        CheckTowerTilt();
        AdjustCameraPosition();
    }

    private void HandleTouchInput()
    {
        if (IsTouchInputDetected())
        {
            SpawnNewBlock();
        }
    }

    private bool IsTouchInputDetected()
    {
#if UNITY_EDITOR
        return Input.GetMouseButtonDown(0);
#else
        return Input.touchCount > 0 && Input.GetTouch(0).phase == TouchPhase.Began;
#endif
    }

    private void SpawnBaseBlock()
    {
        GameObject baseBlock = Instantiate(blockPrefab, Vector3.zero, Quaternion.identity);
        Rigidbody rb = baseBlock.GetComponent<Rigidbody>();
        if (rb != null)
        {
            rb.isKinematic = true;
        }
        towerBlocks.Add(baseBlock);
    }

    private void SpawnNewBlock()
    {
        GameObject lastBlock = towerBlocks[towerBlocks.Count - 1];
        Vector3 spawnPos = lastBlock.transform.position + new Vector3(0, spawnOffset, 0);

        GameObject newBlock = Instantiate(blockPrefab, spawnPos, Quaternion.identity);

        // Procedural Variation
        newBlock.transform.localScale = new Vector3(
            Random.Range(0.8f, 1.2f),
            1f,
            Random.Range(0.8f, 1.2f)
        );
        newBlock.GetComponent<Renderer>().material.color = Random.ColorHSV();

        towerBlocks.Add(newBlock);

        score++;
        UpdateScore();
    }

    private void ApplyTowerSway()
    {
        for (int i = 0; i < towerBlocks.Count; i++)
        {
            Rigidbody rb = towerBlocks[i].GetComponent<Rigidbody>();
            if (rb != null)
            {
                Vector3 randomDirection = new Vector3(
                    Random.Range(-1f, 1f),
                    0f,
                    Random.Range(-1f, 1f)
                ).normalized;

                float forceMultiplier = (i + 1) * swayForce * Time.deltaTime;
                rb.AddForce(randomDirection * forceMultiplier, ForceMode.Force);
            }
        }
    }

    private void CheckTowerTilt()
    {
        if (towerBlocks.Count == 0) return;

        GameObject topBlock = towerBlocks[towerBlocks.Count - 1];
        float tiltAngle = Vector3.Angle(Vector3.up, topBlock.transform.up);

        if (tiltAngle > maxTiltAngle)
        {
            GameOver();
        }
    }

    private void AdjustCameraPosition()
    {
        float towerHeight = 0f;
        if (towerBlocks.Count > 0)
        {
            towerHeight = towerBlocks[towerBlocks.Count - 1].transform.position.y;
        }
        float targetHeight = towerHeight + cameraHeightOffset;
        Vector3 targetPosition = new Vector3(mainCamera.transform.position.x, targetHeight, mainCamera.transform.position.z);
        mainCamera.transform.position = Vector3.Lerp(mainCamera.transform.position, targetPosition, cameraFollowSpeed * Time.deltaTime);
    }

    private void GameOver()
    {
        gameOver = true;
        gameOverText.gameObject.SetActive(true);
    }

    public void ResetGame()
    {
        foreach (var block in towerBlocks)
        {
            Destroy(block);
        }
        towerBlocks.Clear();

        score = 0;
        gameOver = false;
        UpdateScore();
        gameOverText.gameObject.SetActive(false);

        SpawnBaseBlock(); 
    }


    private void UpdateScore()
    {
        if (scoreText != null)
            scoreText.text = $"Score: {score}";
    }
}
